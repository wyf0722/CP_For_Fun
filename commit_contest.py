#!/usr/bin/env python3
"""Auto-commit LeetCode contest solutions with a conventional commit message.

The commit message follows the historical format used in this repo:
    feat(CP_leetcode): weekly511 AB
    feat(CP_leetcode): biweekly185 ABC

Contest type (weekly/biweekly) and number are inferred from the file path:
    CP_leetcode/weekly/510-519/511/A.py      -> weekly511
    CP_leetcode/biweekly/180-189/185/C.py    -> biweekly185

Problem letters are extracted from the file stem (A.py -> A) and joined in
sorted order. Non-problem files such as .gitkeep are ignored.

Usage:
    python commit_contest.py            # commit every changed contest (one commit each)
    python commit_contest.py --dry-run  # preview the commits without writing
    python commit_contest.py --push     # commit and push to origin
"""

from __future__ import annotations

import argparse
import re
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent
CP_DIR = REPO_ROOT / "CP_leetcode"

# A problem file stem is a single uppercase letter, e.g. A, B, C, D.
PROBLEM_RE = re.compile(r"^[A-Z]$")
# Match the contest path: CP_leetcode/<type>/<range>/<number>/<file>
# <type> = weekly | biweekly, <number> = digits.
CONTEST_PATH_RE = re.compile(
    r"^CP_leetcode/(?P<type>weekly|biweekly)/[^/]+/(?P<number>\d+)/(?P<file>.+)$"
)


def run(cmd: list[str], *, check: bool = True, capture: bool = True) -> str:
    """Run a git command inside the repo root and return its stdout."""
    result = subprocess.run(
        cmd,
        cwd=REPO_ROOT,
        capture_output=capture,
        text=True,
    )
    if check and result.returncode != 0:
        sys.stderr.write(result.stderr)
        raise SystemExit(f"Command failed: {' '.join(cmd)}")
    return result.stdout


def get_changed_files() -> list[str]:
    """Return CP_leetcode files that are staged, modified, or untracked."""
    # --porcelain gives stable output; leading status codes flag the state.
    out = run(["git", "status", "--porcelain"])
    files: list[str] = []
    for line in out.splitlines():
        if not line:
            continue
        path = line[3:].strip().strip('"')
        # For renames the format is "R  old -> new"; keep the new path.
        if " -> " in path:
            path = path.split(" -> ", 1)[1]
        if path.startswith("CP_leetcode/"):
            files.append(path)
    return files


def parse_contest(path: str) -> tuple[str, str] | None:
    """Return (contest_label, problem_letter) for a contest solution file.

    contest_label is like "weekly511" or "biweekly185".
    Returns None for non-problem files (e.g. .gitkeep, helper scripts).
    """
    match = CONTEST_PATH_RE.match(path)
    if not match:
        return None
    contest_type = match.group("type")
    number = match.group("number")
    filename = match.group("file")
    stem = Path(filename).stem
    if not PROBLEM_RE.match(stem):
        return None
    return f"{contest_type}{number}", stem


def build_message(contest_label: str, letters: list[str]) -> str:
    """Build the conventional commit message for one contest."""
    joined = "".join(sorted(letters))
    return f"feat(CP_leetcode): {contest_label} {joined}"


def commit_contest(contest_label: str, letters: list[str], paths: list[str],
                   *, dry_run: bool, push: bool) -> None:
    """Stage and commit all files belonging to one contest."""
    message = build_message(contest_label, letters)
    print(f"\n=== {contest_label} ===")
    for p in paths:
        print(f"  + {p}")
    print(f"  message: {message}")

    if dry_run:
        print("  (dry-run, skipped)")
        return

    run(["git", "add", "--", *paths])
    run(["git", "commit", "-m", message])
    if push:
        run(["git", "push"])


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Auto-commit LeetCode contest solutions.",
    )
    parser.add_argument(
        "--dry-run", action="store_true",
        help="preview commits without staging or committing",
    )
    parser.add_argument(
        "--push", action="store_true",
        help="push to origin after committing",
    )
    args = parser.parse_args()

    files = get_changed_files()
    if not files:
        print("No changes under CP_leetcode/ to commit.")
        return 0

    # Group problem files by contest, collecting letters and full paths.
    groups: dict[str, dict[str, list[str]]] = defaultdict(
        lambda: {"letters": [], "paths": []}
    )
    ignored: list[str] = []
    for path in files:
        parsed = parse_contest(path)
        if parsed is None:
            ignored.append(path)
            continue
        contest_label, letter = parsed
        groups[contest_label]["letters"].append(letter)
        groups[contest_label]["paths"].append(path)

    if ignored:
        print("Ignored (not contest problem files):")
        for p in ignored:
            print(f"  - {p}")

    if not groups:
        print("No contest problem files detected; nothing to commit.")
        return 0

    # Commit each contest separately, contest label sorted for stable order.
    for contest_label in sorted(groups, key=lambda c: (c,)):
        data = groups[contest_label]
        commit_contest(
            contest_label,
            data["letters"],
            data["paths"],
            dry_run=args.dry_run,
            push=args.push,
        )

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
