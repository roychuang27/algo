import asyncio
import logging
import os
from pathlib import Path
from urllib.parse import urljoin

import aiofiles
import aiohttp
from bs4 import BeautifulSoup
from dotenv import load_dotenv
from tqdm import tqdm

load_dotenv()

CREDENTIALS = {
    "username": os.getenv("CSES_USERNAME", ""),
    "password": os.getenv("CSES_PASSWORD", ""),
}

BASE_URL = "https://cses.fi/problemset"
LOGIN_URL = "https://cses.fi/login"
HOME_URL = "https://cses.fi/"

HEADERS = {
    "User-Agent": (
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
        "AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36"
    ),
}

OUTPUT_DIR = Path("./cses")

INVALID_FILENAME_CHARS = '<>:"/\\|?*'


def detect_language(raw_lang: str):
    raw_lower = (raw_lang or "").lower()

    if "py" in raw_lower:
        return "Python", "py"
    if "cpp" in raw_lower or "c++" in raw_lower:
        return "C++", "cpp"
    if "java" in raw_lower:
        return "Java", "java"
    if "rust" in raw_lower:
        return "Rust", "rs"
    if "go" in raw_lower:
        return "Go", "go"
    if "javascript" in raw_lower or "node" in raw_lower:
        return "JavaScript", "js"
    if raw_lower == "c" or raw_lower.startswith("c "):
        return "C", "c"
    if "c#" in raw_lower or "csharp" in raw_lower:
        return "C#", "cs"
    if "kotlin" in raw_lower:
        return "Kotlin", "kt"
    if "haskell" in raw_lower:
        return "Haskell", "hs"
    if "scala" in raw_lower:
        return "Scala", "sc"
    if "php" in raw_lower:
        return "PHP", "php"
    if "perl" in raw_lower:
        return "Perl", "pl"
    if "pascal" in raw_lower:
        return "Pascal", "pas"
    if "delphi" in raw_lower:
        return "Delphi", "dpr"

    return "Unknown", "txt"


def safe_filename(name: str) -> str:
    cleaned = "".join("_" if ch in INVALID_FILENAME_CHARS else ch for ch in name)
    return cleaned.strip().rstrip(".")


def extract_result_id(url: str) -> int:
    try:
        return int(url.rstrip("/").split("/")[-1])
    except Exception:
        return -1


async def fetch_text(
    session: aiohttp.ClientSession,
    url: str,
    *,
    method: str = "GET",
    data=None,
    sem: asyncio.Semaphore | None = None,
    retries: int = 3,
    retry_delay: float = 0.5,
) -> str:
    async def _do_request() -> str:
        last_exc = None
        for attempt in range(1, retries + 1):
            try:
                async with session.request(method, url, data=data) as resp:
                    resp.raise_for_status()
                    return await resp.text()
            except Exception as exc:
                last_exc = exc
                if attempt < retries:
                    await asyncio.sleep(retry_delay * attempt)
        raise last_exc

    if sem is not None:
        async with sem:
            return await _do_request()
    return await _do_request()


async def _login(session: aiohttp.ClientSession, sem: asyncio.Semaphore) -> None:
    """Login to CSES using stored credentials."""
    login_html = await fetch_text(session, LOGIN_URL, sem=sem)
    soup = BeautifulSoup(login_html, "html.parser")

    csrf_token = soup.find("input", {"name": "csrf_token"})
    if not csrf_token or not csrf_token.get("value"):
        raise RuntimeError("Failed to get CSRF token from login page")

    payload = {
        "nick": CREDENTIALS["username"],
        "pass": CREDENTIALS["password"],
        "csrf_token": csrf_token["value"],
    }

    await fetch_text(session, LOGIN_URL, method="POST", data=payload, sem=sem)

    home_html = await fetch_text(session, HOME_URL, sem=sem)
    home_soup = BeautifulSoup(home_html, "html.parser")
    account_link = home_soup.find("a", {"class": "account"})

    if not account_link or account_link.get("href") == "/login":
        raise RuntimeError("Login failed - check your credentials")

    print(f"[CSES] Logged in successfully as {CREDENTIALS['username']}")


async def _get_task_urls(
    session: aiohttp.ClientSession, sem: asyncio.Semaphore
) -> list[str]:
    """Scrape all task URLs from the problem set list."""
    resp_html = await fetch_text(session, f"{BASE_URL}/list", sem=sem)
    soup = BeautifulSoup(resp_html, "html.parser")
    task_urls = set()

    for link in soup.find_all("a", href=lambda h: h and "/problemset/task/" in h):
        href = link.get("href")
        if href:
            task_urls.add(urljoin(BASE_URL, href))

    return sorted(task_urls)


async def _get_accepted_submissions(
    session: aiohttp.ClientSession, url: str, sem: asyncio.Semaphore
) -> list[dict]:
    """Find all accepted submissions for a task."""
    resp_html = await fetch_text(session, url, sem=sem)
    soup = BeautifulSoup(resp_html, "html.parser")

    h1 = soup.find("h1")
    h4 = soup.find("h4")
    title = h1.text.strip() if h1 else os.path.basename(url)
    category = h4.text.strip() if h4 else "Uncategorized"

    results = []
    result_links = soup.find_all("a", href=lambda h: h and "/problemset/result/" in h)
    for link in result_links:
        span = link.find("span")
        if span and "full" in span.get("class", []):
            href = link.get("href")
            if not href:
                continue
            result_url = urljoin(BASE_URL, href)
            results.append(
                {
                    "title": title,
                    "category": category,
                    "result_url": result_url,
                    "task_url": url,
                }
            )

    return results


async def _get_submission_code(
    session: aiohttp.ClientSession, prob_info: dict, sem: asyncio.Semaphore
):
    """Fetch submission code and details from result page."""
    resp_html = await fetch_text(session, prob_info["result_url"], sem=sem)
    soup = BeautifulSoup(resp_html, "html.parser")

    table = soup.find("table")
    if not table:
        return None

    details = {}
    for row in table.find_all("tr"):
        cells = row.find_all("td")
        if len(cells) >= 2:
            key = cells[0].text.strip().rstrip(":")
            details[key] = cells[1].text.strip()

    status = details.get("Result", "")
    if status.upper() != "ACCEPTED":
        print(
            f"[CSES] WARNING: Submission {prob_info['result_url']} status is '{status}', not ACCEPTED. Skipping."
        )
        return None

    pre = soup.find("pre", {"class": "linenums"}) or soup.find("pre")
    if not pre:
        return None

    code = pre.get_text()

    raw_lang = details.get("Language", "Unknown")
    folder_lang, extension = detect_language(raw_lang)
    solution_id = prob_info["result_url"].rstrip("/").split("/")[-1]

    return {
        "language": raw_lang,
        "problem_code": os.path.basename(prob_info["task_url"].rstrip("/")),
        "solution_id": solution_id,
        "problem_name": prob_info["title"],
        "problem_link": prob_info["task_url"],
        "solution": code,
        "category": prob_info["category"],
        "extension": extension,
        "folder_lang": folder_lang,
    }


async def _safe_get_accepted_submissions(
    session: aiohttp.ClientSession, url: str, sem: asyncio.Semaphore
) -> list[dict]:
    try:
        return await _get_accepted_submissions(session, url, sem)
    except Exception as e:
        print(f"[CSES] Error fetching task page {url}: {e}")
        return []


async def _safe_get_submission_code(
    session: aiohttp.ClientSession, prob_info: dict, sem: asyncio.Semaphore
):
    try:
        return await _get_submission_code(session, prob_info, sem)
    except Exception as e:
        print(f"[CSES] Error fetching {prob_info.get('title', 'unknown')}: {e}")
        return None


async def _save_solution(solution: dict, sem: asyncio.Semaphore) -> bool:
    try:
        extension = solution.get("extension", "txt")
        folder_lang = solution.get("folder_lang", "Unknown")
        category = solution.get("category", "")
        problem_code = solution["problem_code"]
        problem_name = solution.get("problem_name", "")

        safe_category = safe_filename(category)
        safe_problem_name = safe_filename(problem_name)
        safe_problem_code = safe_filename(problem_code)

        if safe_category and safe_problem_name:
            filename = f"{safe_category}/{safe_problem_code} | {safe_problem_name}.{extension}"
        elif safe_problem_name:
            filename = f"{safe_problem_code} | {safe_problem_name}.{extension}"
        else:
            filename = f"{safe_problem_code}.{extension}"

        path = OUTPUT_DIR / folder_lang / filename
        path.parent.mkdir(parents=True, exist_ok=True)

        solution_code = solution["solution"].replace("\r\n", "\n")

        async with sem:
            async with aiofiles.open(path, "w", encoding="utf-8") as f:
                await f.write(solution_code)

        print(f"[CSES] Successfully saved: {path}")
        print(f"  - Problem: {problem_name}")
        print(f"  - Language: {solution['language']}")
        print(f"  - Solution ID: {solution['solution_id']}")
        return True

    except Exception as e:
        logging.error(f"{e} FOR {solution}")
        return False


async def _safe_save_solution(solution: dict, sem: asyncio.Semaphore):
    ok = await _save_solution(solution, sem)
    return solution, ok


async def _run_with_progress(tasks, desc: str, unit: str):
    results = []
    with tqdm(total=len(tasks), desc=desc, unit=unit) as pbar:
        for coro in asyncio.as_completed(tasks):
            results.append(await coro)
            pbar.update(1)
    return results


async def fetch_from_cses():
    failed = []

    if not CREDENTIALS["username"] or not CREDENTIALS["password"]:
        print("[CSES] Warning: No credentials found in .env file")
        return

    timeout = aiohttp.ClientTimeout(total=60)
    connector = aiohttp.TCPConnector(limit=20, ttl_dns_cache=300)

    fetch_sem = asyncio.Semaphore(10)
    save_sem = asyncio.Semaphore(8)

    async with aiohttp.ClientSession(
        headers=HEADERS,
        timeout=timeout,
        connector=connector,
        cookie_jar=aiohttp.CookieJar(),
    ) as session:
        try:
            await _login(session, fetch_sem)
        except Exception as e:
            print(f"[CSES] Login failed: {e}")
            return

        print("[CSES] Fetching task list...")
        task_urls = await _get_task_urls(session, fetch_sem)
        print(f"[CSES] Found {len(task_urls)} tasks, checking for solutions...")

        task_coros = [
            asyncio.create_task(_safe_get_accepted_submissions(session, url, fetch_sem))
            for url in task_urls
        ]
        task_results = await _run_with_progress(task_coros, "Tasks", "task")

        all_accepted = []
        for submissions in task_results:
            all_accepted.extend(submissions)

        print(
            f"[CSES] Found {len(all_accepted)} total accepted submissions, fetching details..."
        )

        result_coros = [
            asyncio.create_task(_safe_get_submission_code(session, prob_info, fetch_sem))
            for prob_info in all_accepted
        ]
        result_items = await _run_with_progress(result_coros, "Results", "submission")

        # Keep latest per (task, language) using the largest numeric result id.
        best_by_key = {}
        for sol in result_items:
            if not sol:
                continue

            key = (sol["problem_link"], sol["folder_lang"])
            current = best_by_key.get(key)
            if current is None or extract_result_id(sol["solution_id"]) > extract_result_id(
                current["solution_id"]
            ):
                best_by_key[key] = sol

        solved = sorted(
            best_by_key.values(),
            key=lambda x: extract_result_id(x["solution_id"]),
            reverse=True,
        )

        lang_counts = {}
        for s in solved:
            lang = s["folder_lang"]
            lang_counts[lang] = lang_counts.get(lang, 0) + 1

        lang_str = ", ".join(
            f"{v} {k}" for k, v in sorted(lang_counts.items(), key=lambda x: -x[1])
        )
        if not lang_str:
            lang_str = "no languages"

        print(f"[CSES] Found {len(solved)} unique solutions ({lang_str}), saving files...")

        save_coros = [
            asyncio.create_task(_safe_save_solution(solution, save_sem))
            for solution in solved
        ]

        save_results = []
        with tqdm(total=len(save_coros), desc="Saving", unit="file") as pbar:
            for coro in asyncio.as_completed(save_coros):
                solution, ok = await coro
                save_results.append(ok)
                if not ok:
                    failed.append(solution)
                pbar.update(1)

        if failed:
            print(f"\n[CSES] {len(failed)} submissions failed to save.")


async def main():
    await fetch_from_cses()


if __name__ == "__main__":
    asyncio.run(main())
