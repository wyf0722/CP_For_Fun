"""
Auto-create LeetCode weekly/biweekly contest directories following the
project layout:
  CP_leetcode/weekly/<lo>-<lo+9>/<n>/
  CP_leetcode/biweekly/<lo>-<lo+9>/<n>/
where <lo>-<lo+9> is the decimal decade of contest id n (e.g. 510 -> 510-519).

New directories are seeded with a .gitkeep placeholder so git can track empty
directories. The placeholder name deliberately avoids the letters A/B/C/D so
it does not interfere with LC_todo.py's solved-problem scanner, which treats
any file whose name contains those letters as a solved problem.

Contest id computation is mirrored from LC_todo.py so the directory range
stays in sync with the todo list.
"""

from datetime import datetime, timedelta
from pathlib import Path
from zoneinfo import ZoneInfo

# ==================== Constants & paths ====================
WEEKLY: str = "weekly"
BIWEEKLY: str = "biweekly"

# Scan range start (kept in sync with LC_todo.py)
START_WEEKLY: int = 402
START_BIWEEKLY: int = 133

SCRIPT_PATH: Path = Path(__file__).resolve()
BASE_DIR: Path = SCRIPT_PATH.parent
REPO_ROOT: Path = BASE_DIR.parent.parent
LC_DIR: Path = REPO_ROOT / "CP_leetcode"

# Placeholder file (no A/B/C/D letters, so LC_todo.py scanner is unaffected)
KEEP_FILE: str = ".gitkeep"

# Contest id base times (Asia/Shanghai), in sync with LC_todo.py
UTC8 = ZoneInfo("Asia/Shanghai")
WEEKLY_BASE_END: datetime = datetime(2020, 1, 5, 12, 0, 0, tzinfo=UTC8)
BIWEEKLY_BASE_END: datetime = datetime(2020, 1, 12, 0, 0, 0, tzinfo=UTC8)
WEEKLY_BASE_ID: int = 170
BIWEEKLY_BASE_ID: int = 17


# ==================== Contest id computation (mirrors LC_todo.py) ====================
def latest_weekly_id() -> int:
    """Return the most recent ended weekly contest id."""
    weeks_since = 1 + int((datetime.now(UTC8) - WEEKLY_BASE_END) / timedelta(days=7))
    return WEEKLY_BASE_ID + weeks_since - 1


def latest_biweekly_id() -> int:
    """Return the most recent ended biweekly contest id."""
    biweeks_since = 1 + int(
        (datetime.now(UTC8) - BIWEEKLY_BASE_END) / timedelta(days=14)
    )
    return BIWEEKLY_BASE_ID + biweeks_since - 1


# ==================== Core logic ====================
def group_folder(n: int) -> str:
    """Return the decade folder name for contest id n, e.g. 510 -> '510-519'."""
    lo = (n // 10) * 10
    return f"{lo}-{lo + 9}"


def ensure_contest_dir(contest_type: str, n: int) -> bool:
    """Create the contest directory if missing; return True if newly created."""
    contest_dir = LC_DIR / contest_type / group_folder(n) / str(n)
    if contest_dir.exists():
        return False
    contest_dir.mkdir(parents=True, exist_ok=True)
    (contest_dir / KEEP_FILE).touch()
    return True


def clean_gitkeep(contest_type: str, n: int) -> bool:
    """
    如果目录存在，并且目录内除 KEEP_FILE 外还有其他文件，则删除 .gitkeep
    返回True代表本次执行了删除操作
    """
    contest_dir = LC_DIR / contest_type / group_folder(n) / str(n)
    if not contest_dir.is_dir():
        return False

    # 获取目录下所有直接子文件（不递归子文件夹）
    entries = list(contest_dir.iterdir())
    files = [e for e in entries if e.is_file()]

    gitkeep_path = contest_dir / KEEP_FILE
    if not gitkeep_path.exists():
        return False

    # 过滤掉gitkeep，看是否还有别的文件
    other_files = [f for f in files if f.name != KEEP_FILE]
    if len(other_files) > 0:
        gitkeep_path.unlink()
        return True
    return False


def main() -> None:
    if not LC_DIR.exists():
        print(f"[ERROR] LeetCode directory not found: {LC_DIR}")
        return

    latest_w = latest_weekly_id()
    latest_b = latest_biweekly_id()
    print(
        f"[INFO] Ended contest range: "
        f"weekly {START_WEEKLY}-{latest_w}, biweekly {START_BIWEEKLY}-{latest_b}"
    )

    created: list[str] = []
    cleaned: list[str] = []

    for n in range(START_WEEKLY, latest_w + 1):
        if ensure_contest_dir(WEEKLY, n):
            created.append(f"{WEEKLY}/{group_folder(n)}/{n}")
        if clean_gitkeep(WEEKLY, n):
            cleaned.append(f"{WEEKLY}/{group_folder(n)}/{n}")

    for n in range(START_BIWEEKLY, latest_b + 1):
        if ensure_contest_dir(BIWEEKLY, n):
            created.append(f"{BIWEEKLY}/{group_folder(n)}/{n}")
        if clean_gitkeep(BIWEEKLY, n):
            cleaned.append(f"{BIWEEKLY}/{group_folder(n)}/{n}")

    if created:
        print(f"\n[NEW] Created {len(created)} directory(ies):")
        for c in created:
            print(f"  - CP_leetcode/{c}/{KEEP_FILE}")
    else:
        print("\n[OK] Nothing to create; all directories already exist.")

    if cleaned:
        print(f"\n[CLEAN] Remove useless {KEEP_FILE} in {len(cleaned)} dir(s):")
        for c in cleaned:
            print(f"  - CP_leetcode/{c}/{KEEP_FILE}")


if __name__ == "__main__":
    main()