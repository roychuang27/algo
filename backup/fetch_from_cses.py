import os
import json
import logging
from time import sleep
from urllib.parse import urljoin
from dotenv import load_dotenv
from bs4 import BeautifulSoup
import requests

load_dotenv()

CREDENTIALS = {
    "username": os.getenv("CSES_USERNAME", ""),
    "password": os.getenv("CSES_PASSWORD", ""),
}

BASE_URL = "https://cses.fi/problemset"
HEADERS = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36",
}

EXTENSIONS = {
    "c++": "cpp",
    "clang": "cpp",
    "gcc": "c",
    "py": "py",
    "javascript": "js",
    "java": "java",
    "c#": "cs",
    "go": "go",
    "haskell": "hs",
    "kotlin": "kt",
    "delphi": "dpr",
    "pascal": "pas",
    "perl": "pl",
    "php": "php",
    "rust": "rs",
    "scala": "sc",
    "node": "js",
}

OUTPUT_DIR = "./cses/"

COMMENT_FORMATS = {
    "cpp": {"start": "/*", "line": " *", "end": " */"},
    "c": {"start": "/*", "line": " *", "end": " */"},
    "py": {"line": "#"},
    "js": {"start": "/*", "line": " *", "end": " */"},
    "java": {"start": "/*", "line": " *", "end": " */"},
    "cs": {"start": "/*", "line": " *", "end": " */"},
    "go": {"start": "/*", "line": " *", "end": " */"},
    "hs": {"line": "--"},
    "kt": {"start": "/*", "line": " *", "end": " */"},
    "dpr": {"line": "//"},
    "pas": {"start": "{", "line": "  ", "end": "}"},
    "pl": {"line": "#"},
    "php": {"start": "/*", "line": " *", "end": " */"},
    "rs": {"start": "/*", "line": " *", "end": " */"},
    "sc": {"start": "/*", "line": " *", "end": " */"},
    "txt": {"line": "#"},
}


def generate_header(solution, extension):
    fmt = COMMENT_FORMATS.get(extension, {"line": "#"})
    lines = []

    if "start" in fmt:
        lines.append(fmt["start"])
        lines.append(f"{fmt['line']} Submission ID: {solution['solution_id']}")
        if solution.get("problem_name"):
            lines.append(f"{fmt['line']} Problem: {solution['problem_name']}")
        if solution.get("problem_link"):
            lines.append(f"{fmt['line']} Link: {solution['problem_link']}")
        lines.append(fmt["end"])
    else:
        prefix = fmt["line"]
        lines.append(f"{prefix} Submission ID: {solution['solution_id']}")
        if solution.get("problem_name"):
            lines.append(f"{prefix} Problem: {solution['problem_name']}")
        if solution.get("problem_link"):
            lines.append(f"{prefix} Link: {solution['problem_link']}")

    return "\n".join(lines)


def _login(session):
    """Login to CSES using stored credentials."""
    login_url = "https://cses.fi/login"
    resp = session.get(login_url)
    resp.raise_for_status()

    soup = BeautifulSoup(resp.text, "html.parser")
    csrf_token = soup.find("input", {"name": "csrf_token"})
    if not csrf_token:
        raise RuntimeError("Failed to get CSRF token from login page")

    payload = {
        "nick": CREDENTIALS["username"],
        "pass": CREDENTIALS["password"],
        "csrf_token": csrf_token["value"],
    }

    resp = session.post(login_url, data=payload)
    resp.raise_for_status()

    soup = BeautifulSoup(resp.text, "html.parser")
    account_link = soup.find("a", {"class": "account"})
    if account_link and account_link.get("href") == "/login":
        raise RuntimeError("Login failed - check your credentials")

    print(f"[CSES] Logged in successfully as {CREDENTIALS['username']}")


def _get_task_urls(session):
    """Scrape all task URLs from the problem set list."""
    resp = session.get(f"{BASE_URL}/list")
    resp.raise_for_status()

    soup = BeautifulSoup(resp.text, "html.parser")
    task_urls = set()

    for link in soup.find_all("a", href=lambda h: h and "/problemset/task/" in h):
        href = link.get("href")
        task_urls.add(urljoin(BASE_URL, href))

    return list(task_urls)


def _get_accepted_submissions(session, url):
    """Find all accepted submissions for a task. Returns list of submission info."""
    resp = session.get(url)
    resp.raise_for_status()

    soup = BeautifulSoup(resp.text, "html.parser")

    h1 = soup.find("h1")
    h4 = soup.find("h4")
    title = h1.text.strip() if h1 else os.path.basename(url)
    category = h4.text.strip() if h4 else "Uncategorized"

    results = []
    result_links = soup.find_all("a", href=lambda h: h and "/problemset/result/" in h)
    for link in result_links:
        span = link.find("span")
        if span and "full" in span.get("class", []):
            result_url = urljoin(BASE_URL, link.get("href"))
            results.append(
                {
                    "title": title,
                    "category": category,
                    "result_url": result_url,
                    "task_url": url,
                }
            )

    return results


def _get_submission_code(session, prob_info):
    """Fetch submission code and details from result page."""
    resp = session.get(prob_info["result_url"])
    resp.raise_for_status()

    soup = BeautifulSoup(resp.text, "html.parser")

    table = soup.find("table")
    if not table:
        return None

    rows = table.find_all("tr")
    details = {}
    for row in rows:
        cells = row.find_all("td")
        if len(cells) >= 2:
            key = cells[0].text.strip().rstrip(":")
            details[key] = cells[1].text.strip()

    # Verify this is an ACCEPTED submission
    status = details.get("Result", "")
    if status.upper() != "ACCEPTED":
        print(
            f"[CSES] WARNING: Submission {prob_info['result_url']} status is '{status}', not ACCEPTED. Skipping."
        )
        return None

    pre = soup.find("pre", {"class": "linenums"})
    if not pre:
        return None

    code = pre.text

    raw_lang = details.get("Language", "Unknown")
    extension = "txt"
    folder_lang = "Unknown"

    raw_lower = raw_lang.lower()
    if "py" in raw_lower:
        extension = "py"
        folder_lang = "Python"
    elif "cpp" in raw_lower or "c++" in raw_lower:
        extension = "cpp"
        folder_lang = "C++"
    elif "java" in raw_lower:
        extension = "java"
        folder_lang = "Java"
    elif "rust" in raw_lower:
        extension = "rs"
        folder_lang = "Rust"
    elif "go" in raw_lower:
        extension = "go"
        folder_lang = "Go"
    elif "javascript" in raw_lower:
        extension = "js"
        folder_lang = "JavaScript"
    elif raw_lower == "c" or raw_lower.startswith("c "):
        extension = "c"
        folder_lang = "C"

    solution_id = prob_info["result_url"].rstrip("/").split("/")[-1]

    return {
        "language": raw_lang,
        "problem_code": os.path.basename(prob_info["task_url"]),
        "solution_id": solution_id,
        "problem_name": prob_info["title"],
        "problem_link": prob_info["task_url"],
        "solution": code,
        "category": prob_info["category"],
        "extension": extension,
        "folder_lang": folder_lang,
    }


def get_solutions():
    """Main generator - yields solution dicts for all accepted submissions."""
    if not CREDENTIALS["username"] or not CREDENTIALS["password"]:
        print("[CSES] Warning: No credentials found in .env file")
        return

    session = requests.Session()
    session.headers.update(HEADERS)

    try:
        _login(session)
    except Exception as e:
        print(f"[CSES] Login failed: {e}")
        return

    print("[CSES] Fetching task list...")
    task_urls = _get_task_urls(session)
    print(f"[CSES] Found {len(task_urls)} tasks, checking for solutions...")

    # Collect ALL accepted submissions from all tasks
    all_accepted = []
    for url in task_urls:
        submissions = _get_accepted_submissions(session, url)
        all_accepted.extend(submissions)

    print(
        f"[CSES] Found {len(all_accepted)} total accepted submissions, fetching details..."
    )

    # Fetch language info for each, keep only latest per (task, language)
    task_lang_latest = {}  # (task_url, folder_lang) -> latest prob_info
    for prob_info in all_accepted:
        resp = session.get(prob_info["result_url"])
        resp.raise_for_status()
        result_soup = BeautifulSoup(resp.text, "html.parser")

        table = result_soup.find("table")
        if not table:
            continue

        rows = table.find_all("tr")
        details = {}
        for row in rows:
            cells = row.find_all("td")
            if len(cells) >= 2:
                key = cells[0].text.strip().rstrip(":")
                details[key] = cells[1].text.strip()

        raw_lang = details.get("Language", "Unknown")
        raw_lower = raw_lang.lower()
        if "py" in raw_lower:
            folder_lang = "Python"
        elif "cpp" in raw_lower or "c++" in raw_lower:
            folder_lang = "C++"
        elif "java" in raw_lower:
            folder_lang = "Java"
        elif "rust" in raw_lower:
            folder_lang = "Rust"
        elif "go" in raw_lower:
            folder_lang = "Go"
        elif "javascript" in raw_lower:
            folder_lang = "JavaScript"
        elif raw_lower == "c" or raw_lower.startswith("c "):
            folder_lang = "C"
        else:
            folder_lang = "Unknown"

        status = details.get("Result", "")
        if status.upper() != "ACCEPTED":
            continue

        # Keep the latest submission per (task, language)
        # Since result_links are ordered newest first, first one wins
        key = (prob_info["task_url"], folder_lang)
        if key not in task_lang_latest:
            prob_info["folder_lang"] = folder_lang
            task_lang_latest[key] = prob_info

    # Sort by result_url descending (newest first)
    solved = sorted(
        task_lang_latest.values(), key=lambda x: x["result_url"], reverse=True
    )

    lang_counts = {}
    for s in solved:
        lang = s["folder_lang"]
        lang_counts[lang] = lang_counts.get(lang, 0) + 1
    lang_str = ", ".join(
        f"{v} {k}" for k, v in sorted(lang_counts.items(), key=lambda x: -x[1])
    )
    print(f"[CSES] Found {len(solved)} unique solutions ({lang_str}), fetching code...")

    for prob_info in solved:
        try:
            result = _get_submission_code(session, prob_info)
            if result:
                yield result
            else:
                print(f"[CSES] Failed to fetch code for {prob_info['title']}")
            sleep(0.3)
        except Exception as e:
            print(f"[CSES] Error fetching {prob_info['title']}: {e}")


def save_solution(solution):
    try:
        extension = solution.get("extension", "txt")
        folder_lang = solution.get("folder_lang", "Unknown")
        category = solution.get("category", "")
        problem_code = solution["problem_code"]
        problem_name = solution.get("problem_name", "")

        if category and problem_name:
            filename = f"{category}/{problem_code} | {problem_name}.{extension}"
        elif problem_name:
            filename = f"{problem_code} | {problem_name}.{extension}"
        else:
            filename = f"{problem_code}.{extension}"

        path = os.path.join(OUTPUT_DIR, folder_lang, filename)

        os.makedirs(os.path.dirname(path), exist_ok=True)

        solution_code = solution["solution"].replace("\r\n", "\n")
        header = generate_header(solution, extension)

        with open(path, "w", encoding="utf-8", newline="\n") as f:
            f.write(header + "\n\n")
            f.write(solution_code)

        print(f"[CSES] Successfully saved: {path}")
        print(f"  - Problem: {problem_name}")
        print(f"  - Language: {solution['language']}")
        print(f"  - Solution ID: {solution['solution_id']}")
        return True

    except Exception as e:
        logging.error(f"{e} FOR {solution}")
        return False


def fetch_from_cses():
    failed = []
    for solution in get_solutions():
        if not save_solution(solution):
            failed.append(solution)

    if failed:
        print(f"\n[CSES] {len(failed)} submissions failed to save.")


def main():
    fetch_from_cses()


if __name__ == "__main__":
    main()
