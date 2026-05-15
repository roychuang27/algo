import os
import json
import logging
from time import sleep
from json.decoder import JSONDecodeError
from dotenv import load_dotenv
import requests
import undetected_chromedriver as webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.common.exceptions import TimeoutException

load_dotenv()

CODEFORCES_CREDENTIALS = {
    "username": os.getenv("CODEFORCES_USERNAME", ""),
    "password": os.getenv("CODEFORCES_PASSWORD", ""),
}

BASE_URL = "https://codeforces.com"
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

OUTPUT_DIR = "./codeforces/"

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


def get_submission_info(username):
    submissions = json.loads(
        requests.get(f"{BASE_URL}/api/user.status?handle={username}").text
    )["result"]

    for submission in submissions:
        if submission["verdict"] == "OK":
            try:
                if len(submission["author"]["members"]) == 1:
                    yield {
                        "language": submission["programmingLanguage"],
                        "problem_code": f"{submission['problem']['contestId']}{submission['problem']['index']}",
                        "solution_id": submission["id"],
                        "problem_name": submission["problem"].get("name", ""),
                        "problem_link": f"{BASE_URL}/contest/{submission['problem']['contestId']}/problem/{submission['problem']['index']}",
                        "link": f"{BASE_URL}/contest/{submission['contestId']}/submission/{submission['id']}",
                    }
            except KeyError:
                pass


def get_code(driver):
    try:
        lines = driver.find_elements(By.CSS_SELECTOR, "#program-source-text > ol > li")
        if lines:
            return "\n".join(line.text for line in lines)
        return driver.find_element(By.ID, "program-source-text").text
    except Exception:
        return ""


def get_solutions(username, headless=False):
    try:
        all_info = list(get_submission_info(username))
    except JSONDecodeError:
        logging.error(
            "CodeForces API is currently unavailable. Please try again later."
        )
        return

    sub_id_info = {info["solution_id"]: info for info in all_info}

    options = webdriver.ChromeOptions()
    if headless:
        options.add_argument("--headless=new")
    options.add_argument("--window-size=1920,1080")
    options.add_argument("--disable-gpu")
    options.add_argument("--no-sandbox")
    options.add_argument("--disable-dev-shm-usage")
    options.add_argument("--disable-extensions")

    driver = None
    try:
        driver = webdriver.Chrome(options=options, version_main=142)

        print("\n" + "=" * 60)
        print("[CodeForces] Logging in with credentials from .env...")
        print("=" * 60)
        driver.get("https://codeforces.com/enter")

        try:
            WebDriverWait(driver, 10).until(
                EC.presence_of_element_located((By.NAME, "handleOrEmail"))
            )
            driver.find_element(By.NAME, "handleOrEmail").send_keys(
                CODEFORCES_CREDENTIALS["username"]
            )
            driver.find_element(By.NAME, "password").send_keys(
                CODEFORCES_CREDENTIALS["password"]
            )
            driver.find_element(By.CSS_SELECTOR, "input[type='submit']").click()

            WebDriverWait(driver, 10).until(
                EC.presence_of_element_located(
                    (By.CSS_SELECTOR, "a[href*='/profile/']")
                )
            )
            print(
                f"[CodeForces] Logged in successfully as {CODEFORCES_CREDENTIALS['username']}"
            )
        except TimeoutException:
            print(
                "[CodeForces] Warning: Login may have failed, will try to fetch anyway..."
            )

        print("=" * 60 + "\n")

        for sub_id, info in sub_id_info.items():
            try:
                print(f"[CodeForces] Fetching solution {sub_id}...")
                driver.get(info["link"])

                try:
                    WebDriverWait(driver, 30).until(
                        EC.presence_of_element_located((By.ID, "program-source-text"))
                    )
                except TimeoutException:
                    print(
                        f"[CodeForces] Timeout waiting for solution {sub_id}. Cloudflare may be blocking."
                    )
                    continue

                code = get_code(driver)
                if code:
                    info["solution"] = code.replace("\u00a0", "\n")
                    yield info
                else:
                    print(f"[CodeForces] No code found for solution {sub_id}")
                sleep(0.5)

            except Exception as e:
                print(f"[CodeForces] Failed to fetch {sub_id}: {e}")
                continue

    finally:
        if driver:
            try:
                driver.close()
                driver.quit()
            except Exception:
                pass


def save_solution(solution):
    try:
        s = solution["language"].lower()
        extension = "txt"
        for key, value in EXTENSIONS.items():
            if key in s:
                extension = value
                break

        folder_map = {
            "cpp": "C++",
            "c": "C",
            "py": "Python",
            "js": "JavaScript",
            "java": "Java",
            "cs": "C#",
            "go": "Go",
            "hs": "Haskell",
            "kt": "Kotlin",
            "dpr": "Delphi",
            "pas": "Pascal",
            "pl": "Perl",
            "php": "PHP",
            "rs": "Rust",
            "sc": "Scala",
            "txt": "Unknown",
        }
        folder_lang = folder_map.get(extension, "Unknown")

        problem_name = solution.get("problem_name", "")
        problem_code = solution["problem_code"]

        if problem_name:
            filename = f"{problem_code} | {problem_name}.{extension}"
        else:
            filename = f"{problem_code}.{extension}"

        path = os.path.join(OUTPUT_DIR, folder_lang, filename)

        if os.path.exists(path):
            print(f"[CodeForces] Skipped {path} (Already exists, keeping the latest)")
            return True

        os.makedirs(os.path.dirname(path), exist_ok=True)

        solution_code = solution["solution"].replace("\r\n", "\n")
        header = generate_header(solution, extension)

        with open(path, "w", encoding="utf-8", newline="\n") as f:
            f.write(header + "\n\n")
            f.write(solution_code)

        print(f"[CodeForces] Successfully saved: {path}")
        print(f"  - Problem: {problem_name}")
        print(f"  - Language: {solution['language']}")
        print(f"  - Solution ID: {solution['solution_id']}")
        return True

    except Exception as e:
        logging.error(f"{e} FOR {solution}")
        return False


def fetch_from_codeforces(username=None, retry_count=3):
    if not username:
        username = CODEFORCES_CREDENTIALS["username"]

    if not username:
        print(
            "[CodeForces] Warning: No username provided. Set CODEFORCES_USERNAME in .env or pass as argument."
        )
        return

    failed = []
    for solution in get_solutions(username, headless=False):
        if not save_solution(solution):
            failed.append(solution)

    for _ in range(retry_count):
        if not failed:
            break

        sleep(180)

        new_failed = []
        for solution in get_solutions(username, headless=False):
            if solution["solution_id"] in [s["solution_id"] for s in failed]:
                if not save_solution(solution):
                    new_failed.append(solution)

        failed = new_failed

    if failed:
        print(f"\n[CodeForces] {len(failed)} submissions failed to save.")


def main():
    fetch_from_codeforces()


if __name__ == "__main__":
    main()
