import asyncio
import logging
import os
import re
from pathlib import Path

import aiofiles
import aiohttp
from bs4 import BeautifulSoup
from tqdm import tqdm

HEADERS = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.5005.63 Safari/537.36",
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

OUTPUT_DIR = Path("./atcoder/")

SOLUTION_ID_RE = re.compile(r"Submission ID:\s*(\d+)")


def read_existing_solution_id(path: Path) -> int | None:
    """Parse an existing file's header to extract its Submission ID."""
    try:
        if not path.exists():
            return None
        with open(path, "r", encoding="utf-8") as f:
            header = f.read(512)
        m = SOLUTION_ID_RE.search(header)
        if m:
            return int(m.group(1))
    except Exception:
        pass
    return None


def resolve_extension(language: str) -> str:
    s = language.lower()
    for key, value in EXTENSIONS.items():
        if key in s:
            return value
    return "txt"


async def fetch_text(
    session: aiohttp.ClientSession,
    url: str,
    *,
    sem: asyncio.Semaphore | None = None,
    retries: int = 5,
    retry_delay: float = 1.0,
    min_interval: float = 0.0,
) -> str:
    async def _do_request() -> str:
        last_exc = None
        for attempt in range(1, retries + 1):
            try:
                async with session.get(url) as resp:
                    if resp.status == 429:
                        wait = retry_delay * (2 ** (attempt - 1))
                        retry_after = resp.headers.get("Retry-After")
                        if retry_after:
                            try:
                                wait = max(wait, float(retry_after))
                            except ValueError:
                                pass
                        print(f"[Atcoder] 429 rate-limited on {url}, waiting {wait:.1f}s...")
                        await asyncio.sleep(wait)
                        continue
                    resp.raise_for_status()
                    return await resp.text()
            except Exception as exc:
                last_exc = exc
                if attempt < retries:
                    await asyncio.sleep(retry_delay * attempt)
        raise last_exc

    if sem is not None:
        async with sem:
            result = await _do_request()
            if min_interval > 0:
                await asyncio.sleep(min_interval)
            return result
    return await _do_request()


async def get_submission_info(
    session: aiohttp.ClientSession, username: str, sem: asyncio.Semaphore
) -> list[dict]:
    """Fetch all accepted submissions from the AtCoder API."""
    submissions = []
    cur = 0

    while True:
        try:
            text = await fetch_text(
                session,
                f"https://kenkoooo.com/atcoder/atcoder-api/v3/user/submissions?user={username}&from_second={cur}",
                sem=sem,
            )
            data = await asyncio.to_thread(
                __import__("json").loads, text
            )
        except Exception as e:
            print(f"[Atcoder] Error fetching submissions page (from_second={cur}): {e}")
            break

        if not data:
            break

        for sub in data:
            if sub["result"] == "AC":
                try:
                    submissions.append({
                        "language": sub["language"],
                        "problem_code": sub["problem_id"],
                        "solution_id": sub["id"],
                        "problem_link": f"https://atcoder.jp/contests/{sub['contest_id']}/tasks/{sub['problem_id']}",
                        "link": f"https://atcoder.jp/contests/{sub['contest_id']}/submissions/{sub['id']}",
                    })
                except KeyError:
                    pass
            cur = sub["epoch_second"] + 1

        await asyncio.sleep(1)

    return submissions


def parse_code(html: str) -> str:
    soup = BeautifulSoup(html, "lxml")
    code_element = soup.select_one("#submission-code")
    if code_element:
        return code_element.text
    return ""


async def get_solutions(
    session: aiohttp.ClientSession,
    username: str,
    sem: asyncio.Semaphore,
    all_info: list[dict] | None = None,
) -> list[dict]:
    """Fetch solution code for each submission info entry."""
    if all_info is None:
        all_info = await get_submission_info(session, username, sem)

    results = []

    async def _fetch_one(info: dict) -> dict | None:
        try:
            html = await fetch_text(session, info["link"], sem=sem, retries=5, min_interval=1)
            code = await asyncio.to_thread(parse_code, html)
            if code:
                return {
                    "language": info["language"],
                    "problem_code": info["problem_code"],
                    "solution_id": info["solution_id"],
                    "problem_link": info["problem_link"],
                    "link": info["link"],
                    "solution": code,
                }
        except Exception as e:
            print(f"[Atcoder] Error fetching solution {info['solution_id']}: {e}")
        return None

    tasks = [asyncio.create_task(_fetch_one(info)) for info in all_info]
    with tqdm(total=len(tasks), desc="Fetching", unit="submission") as pbar:
        for coro in asyncio.as_completed(tasks):
            result = await coro
            if result:
                results.append(result)
            pbar.update(1)

    return results


async def save_solution(solution: dict) -> bool:
    try:
        extension = resolve_extension(solution["language"])

        filename = (
            f"{solution['problem_code']} | {solution['problem_name']}.{extension}"
            if solution.get("problem_name", "")
            else f"{solution['problem_code']}.{extension}"
        )
        path = OUTPUT_DIR / filename
        path.parent.mkdir(parents=True, exist_ok=True)

        new_id = solution["solution_id"]
        existing_id = read_existing_solution_id(path)

        if existing_id is not None:
            if existing_id >= new_id:
                print(f"[Atcoder] Skipped {path} (existing ID {existing_id} >= new ID {new_id})")
                return True
            print(f"[Atcoder] Updating {path} (existing ID {existing_id} < new ID {new_id})")

        solution_code = solution["solution"].replace("\r\n", "\n")

        async with aiofiles.open(path, "w", encoding="utf-8", newline="\n") as f:
            await f.write(solution_code)

        print(f"[Atcoder] Successfully saved: {path}")
        print(f"  - Problem: {solution.get('problem_name', solution['problem_code'])}")
        print(f"  - Language: {solution['language']}")
        print(f"  - Solution ID: {solution['solution_id']}")
        return True

    except Exception as e:
        logging.error(f"{e} FOR {solution}")
        return False


async def _safe_save_solution(solution: dict):
    ok = await save_solution(solution)
    return solution, ok


async def fetch_from_atcoder(atcoder_username: str):
    timeout = aiohttp.ClientTimeout(total=60)
    connector = aiohttp.TCPConnector(limit=10, ttl_dns_cache=300)
    sem = asyncio.Semaphore(4)

    async with aiohttp.ClientSession(
        headers=HEADERS,
        timeout=timeout,
        connector=connector,
    ) as session:
        print(f"[Atcoder] Fetching submissions for {atcoder_username}...")
        solutions = await get_solutions(session, atcoder_username, sem)
        print(f"[Atcoder] Fetched {len(solutions)} solutions, saving...")

        failed = []
        save_coros = [
            asyncio.create_task(_safe_save_solution(sol)) for sol in solutions
        ]
        with tqdm(total=len(save_coros), desc="Saving", unit="file") as pbar:
            for coro in asyncio.as_completed(save_coros):
                solution, ok = await coro
                if not ok:
                    failed.append(solution)
                pbar.update(1)

        for attempt in range(3):
            if not failed:
                break
            print(f"[Atcoder] Retrying {len(failed)} failed submissions (attempt {attempt + 1}/3)...")
            await asyncio.sleep(180)
            retry_solutions = await get_solutions(session, atcoder_username, sem, failed)
            new_failed = []
            for sol in retry_solutions:
                if not await save_solution(sol):
                    new_failed.append(sol)
            failed = new_failed


async def main():
    await fetch_from_atcoder("roychuang")


if __name__ == "__main__":
    asyncio.run(main())
