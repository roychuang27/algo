#!/usr/bin/env python3

import json
import os
import sys
from pathlib import Path


SCRIPT_DIR = Path(__file__).resolve().parent
SOURCE = SCRIPT_DIR / "starter.cpp"

CONFIG_HOME = Path(
    os.environ.get("XDG_CONFIG_HOME", Path.home() / ".config")
)

OUTPUT = CONFIG_HOME / "helix" / "snippets" / "cpp.json"


def main():
    if not OUTPUT.is_file():
        raise FileNotFoundError(f"Not found: {OUTPUT}")

    # No arguments: update the default "cp" snippet.
    if len(sys.argv) == 1:
        files = [(SOURCE, "cp")]
    else:
        # Arguments: each file becomes a snippet named after its stem.
        files = [
            (Path(filename), Path(filename).stem)
            for filename in sys.argv[1:]
        ]

    snippets = json.loads(OUTPUT.read_text(encoding="utf-8"))

    for source, name in files:
        if not source.is_file():
            raise FileNotFoundError(f"Not found: {source}")

        body = source.read_text(encoding="utf-8").splitlines()

        snippets[name] = {
            "prefix": name,
            "body": body,
        }

    OUTPUT.write_text(
        json.dumps(
            snippets,
            indent=4,
            ensure_ascii=False,
        ) + "\n",
        encoding="utf-8",
    )

    print(f"Updated {len(files)} snippet(s) in {OUTPUT}")


if __name__ == "__main__":
    main()
