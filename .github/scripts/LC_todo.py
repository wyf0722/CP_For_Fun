import os
import re
import json
from collections import defaultdict
from typing import Dict, Set, List, Tuple
from pathlib import Path

# ==================== 常量与配置 ====================
TARGET_PROBLEMS: Set[str] = set('ABCD')
BIWEEKLY: str = 'biweekly'
WEEKLY: str = 'weekly'
CONTEST_LINK: str = 'https://leetcode.cn/contest/'

# 路径配置
SCRIPT_PATH: Path = Path(__file__).resolve()
BASE_DIR: Path = SCRIPT_PATH.parent
REPO_ROOT: Path = BASE_DIR.parent.parent
CODE_DIR: Path = REPO_ROOT / 'CP_leetcode'
OUTPUT_DIR: Path = BASE_DIR.parent / 'leetcode'
OUTPUT_FILE: Path = OUTPUT_DIR / 'contest_todo.md'  # 改为 md 格式
RATINGS_FILE: Path = OUTPUT_DIR / 'leetcode_ratings.json'

# ==================== 核心功能函数 ====================
def get_tag(rating: float) -> Tuple[str, str]:
    """根据难度Rating返回对应标签和图标"""
    if rating < 2000:
        return ('🍰', 'Easy')
    elif rating < 2200:
        return ('🛀', 'Medium')
    elif rating < 2400:
        return ('🚬', 'Hard')
    elif rating < 2600:
        return ('🔪', 'Expert')
    elif rating < 2800:
        return ('🔫', 'Master')
    else:
        return ('💣', 'Legend')

def get_problem_ratings() -> Dict[Tuple[str, str], float]:
    """加载题目Rating映射表"""
    problem_ratings: Dict[Tuple[str, str], float] = {}
    try:
        with open(RATINGS_FILE, 'r', encoding='utf-8') as f:
            ratings_data = json.load(f)
            for problem in ratings_data:
                contest_id = problem['ContestSlug']
                problem_idx = chr(ord('A') + int(problem['ProblemIndex'][1]) - 1)
                rating = problem['Rating']
                if re.match(r'(weekly|biweekly)-contest-\d+', contest_id):
                    key = (contest_id, problem_idx)
                    if key not in problem_ratings:
                        problem_ratings[key] = rating
        print(f"✅ 成功加载Rating数据，共 {len(problem_ratings)} 道题目")
    except FileNotFoundError:
        print(f"⚠️  Rating文件未找到: {RATINGS_FILE}，将显示未知Rating")
    except json.JSONDecodeError:
        print(f"⚠️  Rating文件JSON格式错误，请检查文件内容")
    except Exception as e:
        print(f"⚠️  加载Rating数据异常: {str(e)}")
    return problem_ratings

def get_unsolved_problems() -> Dict[str, List[str]]:
    """扫描代码目录，生成未解决题目清单"""
    unsolved_by_contest: Dict[str, List[str]] = defaultdict(list)
    problem_ratings = get_problem_ratings()
    total_unsolved = 0

    if not CODE_DIR.exists():
        print(f"❌  错误：代码目录不存在！请检查路径: {CODE_DIR}")
        return unsolved_by_contest
    print(f"\n🔍  开始扫描代码目录: {CODE_DIR}\n")

    for root, dirs, files in os.walk(CODE_DIR):
        # 完全按原代码逻辑：跳过非叶子目录
        if dirs:
            print(f"⏭️  跳过非叶子目录: {root}")
            continue
            
        path_components = Path(root).parts
        if len(path_components) < 3:
            continue
        
        contest_type = ''
        if WEEKLY in path_components:
            contest_type = WEEKLY
        elif BIWEEKLY in path_components:
            contest_type = BIWEEKLY
        else:
            continue
        
        contest_num = path_components[-1]
        contest_id = f"{contest_type}-contest-{contest_num}"

        print(f"📂 扫描到叶子比赛目录: {root}")
        print(f"   解析比赛ID: {contest_id}")

        solved_problems = {
            problem
            for problem in TARGET_PROBLEMS
            for file in files if problem in file
        }
        unsolved_problems = sorted(TARGET_PROBLEMS - solved_problems)

        print(f"   已解决: {sorted(solved_problems)} | 未解决: {unsolved_problems}\n")

        if unsolved_problems:
            unsolved_by_contest[contest_id] = unsolved_problems
            total_unsolved += len(unsolved_problems)

    _write_output_file(unsolved_by_contest, problem_ratings, total_unsolved)
    return unsolved_by_contest

def _write_output_file(
    unsolved: Dict[str, List[str]],
    ratings: Dict[Tuple[str, str], float],
    total: int
) -> None:
    """将结果写入Markdown格式的输出文件"""
    OUTPUT_DIR.mkdir(exist_ok=True, parents=True)
    
    with open(OUTPUT_FILE, 'w', encoding='utf-8') as f:
        # 1. 标题
        f.write("# 💜 LeetCode 未解决竞赛题目清单\n\n")
        f.write("---\n\n")
        
        # 2. 总统计
        f.write("## 📊 总统计\n\n")
        f.write(f"- 待完成比赛：**{len(unsolved)}** 场\n")
        f.write(f"- 待完成题目：**{total}** 道\n\n")
        
        # 3. 难度说明
        f.write("## 📋 难度等级说明\n\n")
        f.write("| 图标 | 难度等级 | 分数范围       |\n")
        f.write("|------|----------|----------------|\n")
        f.write("| 🍰   | Easy     | Rating < 2000  |\n")
        f.write("| 🛀   | Medium   | 2000 ≤ Rating < 2200 |\n")
        f.write("| 🚬   | Hard     | 2200 ≤ Rating < 2400 |\n")
        f.write("| 🔪   | Expert   | 2400 ≤ Rating < 2600 |\n")
        f.write("| 🔫   | Master   | 2600 ≤ Rating < 2800 |\n")
        f.write("| 💣   | Legend   | Rating ≥ 2800  |\n\n")
        
        # 4. 比赛详情
        f.write("## 🏆 未解决题目详情\n\n")
        f.write("---\n\n")
        
        for contest_id in sorted(
            unsolved.keys(),
            key=lambda x: (
                0 if WEEKLY in x else 1,
                int(re.search(r'\d+', x).group()) if re.search(r'\d+', x) else 0
            )
        ):
            problems = unsolved[contest_id]
            contest_link = f"{CONTEST_LINK}{contest_id}/"
            
            f.write(f"### 🏆 {contest_id}\n\n")
            f.write(f"🔗 比赛链接：[{contest_link}]({contest_link})\n\n")
            f.write("#### 📝 题目列表\n\n")
            
            for problem in problems:
                rating = ratings.get((contest_id, problem))
                if rating:
                    icon, level = get_tag(rating)
                    f.write(
                        f"- {icon} **Problem {problem}** | "
                        f"Rating: **{rating:4.0f}** | "
                        f"难度: {level}\n"
                    )
                else:
                    f.write(
                        f"- 🔹 **Problem {problem}** | "
                        f"Rating: 未知 | 难度: 待评估\n"
                    )
            f.write("\n")

    print(f"\n🎉  未解决题目清单已生成！")
    print(f"📄  输出文件路径: {OUTPUT_FILE}")

# ==================== 主程序入口 ====================
if __name__ == '__main__':
    get_unsolved_problems()