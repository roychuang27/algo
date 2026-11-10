#!/usr/bin/env python3

"""Builds and runs the cases in tests/cases against the templates.

Each case imitates how the snippets are used: the template headers are
appended to starter.cpp and everything is compiled as one file. A case looks
like this:

    // std: c++23 c++17            standards to build with (default c++23)
    // mode: full                  full (default) or prelude
    // headers: modint.hpp         templates appended to the file
    // defines: SHELTER             macros to define while compiling
    --- code
    <the code>
    --- out: c++23
    <expected stdout for c++23, `--- out` alone covers every standard>
    --- err has
    <substrings expected on stderr, ANSI escapes stripped>

`mode: full` puts the code where `${1}` is, so the case runs inside
single_testcase(). `mode: prelude` appends the code after everything above
`#if defined(SHELTER)` instead, which is handy for testing the macros on
their own and requires the case to define its own main().
"""

import re
import subprocess
import sys
import tempfile
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
CASES = ROOT / "tests" / "cases"
STARTER = ROOT / "starter.cpp"
PRELUDE_END = "#if defined(SHELTER)"
FLAGS = ["-Wall", "-Wextra", "-O2"]
ANSI = re.compile(r"\x1b\[[0-9;]*m")


def parse(path):
    meta = {"std": ["c++23"], "mode": "full", "headers": [], "defines": []}
    sections = {}
    lines = path.read_text().splitlines()
    current = None
    for line in lines:
        if line.startswith("--- "):
            current = line[4:].strip()
            sections.setdefault(current, [])
            continue
        if current is None:
            key, _, value = line.removeprefix("// ").partition(":")
            if line.startswith("// ") and key in meta:
                meta[key] = value.split() if key != "mode" else value.strip()
            continue
        sections[current].append(line)
    return meta, sections


def assemble(meta, code):
    starter = STARTER.read_text()
    headers = "\n".join((ROOT / name).read_text() for name in meta["headers"])
    if meta["mode"] == "prelude":
        return starter.split(PRELUDE_END)[0] + headers + "\n" + code
    body = starter.replace("${1}", code, 1)
    anchor = "void single_testcase() {"
    return body.replace(anchor, headers + "\n" + anchor, 1)


def expected(sections, name, std):
    tagged = sections.get(f"{name}: {std}")
    return sections.get(name) if tagged is None else tagged


def tidy(text):
    return "\n".join(line.rstrip() for line in text.rstrip().splitlines())


def run(case):
    meta, sections = parse(case)
    failures = 0
    for std in meta["std"]:
        label = f"{case.name} [{std}]"
        with tempfile.TemporaryDirectory() as tmp:
            tmp = Path(tmp)
            source = tmp / "main.cpp"
            source.write_text(assemble(meta, "\n".join(sections["code"])))
            binary = tmp / "main"
            build = subprocess.run(
                [
                    "g++",
                    f"-std={std}",
                    *FLAGS,
                    *(f"-D{name}" for name in meta["defines"]),
                    "-o",
                    binary,
                    source,
                ],
                capture_output=True,
                text=True,
            )
            if build.returncode != 0:
                print(f"FAIL {label}: compile error")
                print(build.stderr.rstrip())
                failures += 1
                continue
            result = subprocess.run(
                [binary], capture_output=True, text=True, timeout=60
            )
        problems = []
        want = expected(sections, "out", std)
        if want is not None and tidy(result.stdout) != tidy("\n".join(want)):
            problems.append(f"stdout\n--- want\n{tidy(chr(10).join(want))}\n"
                            f"--- got\n{tidy(result.stdout)}")
        for needle in expected(sections, "err has", std) or []:
            if needle and needle not in ANSI.sub("", result.stderr):
                problems.append(f"stderr missing {needle!r}\n{result.stderr}")
        if problems:
            print(f"FAIL {label}")
            print("\n".join(problems))
            failures += 1
        else:
            print(f"ok   {label}")
    return failures


def main():
    cases = sorted(CASES.glob("*.cpp"))
    if not cases:
        print("no cases found")
        return 1
    failures = sum(run(case) for case in cases)
    print(f"\n{len(cases)} cases, {failures} failure(s)")
    return 1 if failures else 0


if __name__ == "__main__":
    sys.exit(main())
