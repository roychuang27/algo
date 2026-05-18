import os
import asyncio
import logging
from urllib.parse import urljoin

import aiohttp
from bs4 import BeautifulSoup
from dotenv import load_dotenv
from tqdm import tqdm

load_dotenv()

# ======================
# CONFIG
# ======================

BASE_URL = "https://cses.fi/problemset"

HEADERS = {
    "User-Agent": "Mozilla/5.0",
}

CREDENTIALS = {
    "username": os.getenv("CSES_USERNAME", ""),
    "password": os.getenv("CSES_PASSWORD", ""),
}

OUTPUT_DIR = "./cses/"

TASK_SEM = asyncio.Semaphore(10)
SUB_SEM = asyncio.Semaphore(10)


# ======================
# LOGIN
# ======================

async def login(session):
    url = "https://cses.fi/login"

    async with session.get(url) as resp:
        html = await resp.text()

    soup = BeautifulSoup(html, "html.parser")
    csrf = soup.find("input", {"name": "csrf_token"})
    if not csrf:
        raise RuntimeError("CSRF token missing")

    payload = {
        "nick": CREDENTIALS["username"],
        "pass": CREDENTIALS["password"],
        "csrf_token": csrf["value"],
    }

    async with session.post(url, data=payload) as resp:
        html = await resp.text()

    if "/login" in html:
        raise RuntimeError("Login failed")

    print(f"[CSES] Logged in as {CREDENTIALS['username']}")


# ======================
# TASK LIST
# ======================

async def get_task_urls(session):
    async with session.get(f"{BASE_URL}/list") as resp:
        html = await resp.text()

    soup = BeautifulSoup(html, "html.parser")

    urls = set()
    for a in soup.find_all("a", href=lambda h: h and "/problemset/task/" in h):
        urls.add(urljoin(BASE_URL, a["href"]))

    return list(urls)


# ======================
# SUBMISSIONS
# ======================

async def get_accepted_submissions(session, url):
    async with TASK_SEM:
        async with session.get(url) as resp:
            html = await resp.text()

    soup = BeautifulSoup(html, "html.parser")

    title = soup.find("h1").text.strip() if soup.find("h1") else url
    category = soup.find("h4").text.strip() if soup.find("h4") else "Uncategorized"

    results = []

    for link in soup.find_all("a", href=lambda h: h and "/problemset/result/" in h):
        span = link.find("span")
        if span and "full" in span.get("class", []):
            results.append({
                "title": title,
                "category": category,
                "result_url": urljoin(BASE_URL, link["href"]),
                "task_url": url,
            })

    return results


# ======================
# FETCH CODE
# ======================

async def fetch_submission(session, prob_info):
    async with SUB_SEM:
        async with session.get(prob_info["result_url"]) as resp:
            html = await resp.text()

    soup = BeautifulSoup(html, "html.parser")

    table = soup.find("table")
    if not table:
        return None

    details = {}
    for row in table.find_all("tr"):
        cells = row.find_all("td")
        if len(cells) >= 2:
            k = cells[0].text.strip().rstrip(":")
            v = cells[1].text.strip()
            details[k] = v

    if details.get("Result", "").upper() != "ACCEPTED":
        return None

    pre = soup.find("pre", {"class": "linenums"})
    if not pre:
        return None

    code = pre.text

    lang = details.get("Language", "").lower()

    if "py" in lang:
        ext, folder = "py", "Python"
    elif "cpp" in lang or "c++" in lang:
        ext, folder = "cpp", "C++"
    elif "java" in lang:
        ext, folder = "java", "Java"
    elif "rust" in lang:
        ext, folder = "rs", "Rust"
    elif "go" in lang:
        ext, folder = "go", "Go"
    elif "javascript" in lang:
        ext, folder = "js", "JavaScript"
    elif "c#" in lang:
        ext, folder = "cs", "CSharp"
    elif lang.startswith("c"):
        ext, folder = "c", "C"
    else:
        ext, folder = "txt", "Unknown"

    return {
        "language": details.get("Language", "Unknown"),
        "problem_code": os.path.basename(prob_info["task_url"]),
        "solution_id": prob_info["result_url"].rstrip("/").split("/")[-1],
        "problem_name": prob_info["title"],
        "problem_link": prob_info["task_url"],
        "solution": code,
        "category": prob_info["category"],
        "extension": ext,
        "folder_lang": folder,
    }


# ======================
# SAVE (UNCHANGED FORMAT)
# ======================

def save_solution(solution):
    try:
        extension = solution.get("extension", "txt")
        folder_lang = solution.get("folder_lang", "Unknown")
        category = solution.get("category", "")
        problem_code = solution["problem_code"]
        problem_name = solution.get("problem_name", "")

        # 🔥 EXACT ORIGINAL FILENAME LOGIC PRESERVED
        if category and problem_name:
            filename = f"{category}/{problem_code} | {problem_name}.{extension}"
        elif problem_name:
            filename = f"{problem_code} | {problem_name}.{extension}"
        else:
            filename = f"{problem_code}.{extension}"

        path = os.path.join(OUTPUT_DIR, folder_lang, filename)

        os.makedirs(os.path.dirname(path), exist_ok=True)

        with open(path, "w", encoding="utf-8") as f:
            f.write(solution["solution"])

        print(f"[Saved] {path}")
        return True

    except Exception as e:
        logging.error(f"{e} FOR {solution}")
        return False


# ======================
# PIPELINE
# ======================

async def get_solutions():
    timeout = aiohttp.ClientTimeout(total=60)

    async with aiohttp.ClientSession(headers=HEADERS, timeout=timeout) as session:
        await login(session)

        print("[CSES] Fetching tasks...")
        task_urls = await get_task_urls(session)

        print(f"[CSES] Found {len(task_urls)} tasks")

        # STEP 1: tasks concurrently
        task_jobs = [get_accepted_submissions(session, url) for url in task_urls]

        all_submissions = []
        for f in tqdm(asyncio.as_completed(task_jobs),
                      total=len(task_jobs),
                      desc="Scanning tasks"):
            all_submissions.extend(await f)

        print(f"[CSES] Found {len(all_submissions)} submissions")

        # STEP 2: submissions concurrently
        sub_jobs = [fetch_submission(session, p) for p in all_submissions]

        solved = []
        for f in tqdm(asyncio.as_completed(sub_jobs),
                      total=len(sub_jobs),
                      desc="Fetching solutions"):
            res = await f
            if res:
                solved.append(res)

        return solved


async def main():
    solutions = await get_solutions()

    for sol in tqdm(solutions, desc="Saving"):
        save_solution(sol)


if __name__ == "__main__":
    asyncio.run(main())
