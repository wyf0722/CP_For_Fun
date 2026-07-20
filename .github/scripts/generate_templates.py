import json
import os
from pathlib import Path

VALID_EXTS = (".cpp", ".hpp", ".py")


def read_template_files(directory: Path) -> dict[str, dict[str, str]]:
    """遍历目录，按相对路径分类收集模板文件内容。

    沿用 os.walk 以保持与历史一致的遍历顺序（与文件系统返回顺序一致），
    避免重新生成时改变 JSON 中分类与文件的出现顺序。
    """
    templates: dict[str, dict[str, str]] = {}
    for root, _, files in os.walk(directory):
        # 相对路径作为分类，统一使用正斜杠以保证跨平台一致
        rel_path = Path(root).relative_to(directory)
        category = "root" if str(rel_path) == "." else rel_path.as_posix()
        bucket = templates.setdefault(category, {})

        for file in files:
            if not file.endswith(VALID_EXTS):
                continue
            bucket[file] = (Path(root) / file).read_text(encoding="utf-8")

    return templates


def main() -> None:
    base_dir = Path(__file__).parent.parent.parent
    pages_dir = base_dir / ".github" / "pages"
    pages_dir.mkdir(exist_ok=True, parents=True)

    # 生成 C++ 和 Python 模板 JSON
    for lang, dir_name in [("cpp", "Copypasta_Cpp"), ("python", "Copypasta_Python")]:
        templates = read_template_files(base_dir / dir_name)
        (pages_dir / f"templates_{lang}.json").write_text(
            json.dumps(templates, ensure_ascii=False, indent=2), encoding="utf-8"
        )


if __name__ == "__main__":
    main()
