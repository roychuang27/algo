#!/usr/bin/env python3

import re
import subprocess
from pathlib import Path


HEADERS = [
    "convolution",
    "dsu",
    "fenwicktree",
    "lazysegtree",
    "math",
    "maxflow",
    "mincostflow",
    "modint",
    "scc",
    "segtree",
    "string",
    "twosat",
]


def expand_header(name: str) -> list[str]:
    result = subprocess.run(
        [
            "python3",
            "expander.py",
            f"atcoder/{name}",
            "-c",
            "--lib",
            "atcoder",
        ],
        check=True,
        stdout=subprocess.PIPE,
        text=True,
    )
    lines: list[str] = []
    for line in result.stdout.splitlines():
        stripped = line.strip()
        if not stripped or stripped.startswith("#line"):
            continue
        lines.append(line.rstrip())
    return lines


def main() -> None:
    target = Path("cpp.snippets")
    with target.open("w", encoding="utf-8") as out:
        for name in HEADERS:
            lines = expand_header(name)
            description = f"AtCoder {name} (expanded)"
            out.write(f"snippet acl_{name} {description}\n")
            for line in lines:
                out.write(f"\t{line}\n")


if __name__ == "__main__":
    main()
