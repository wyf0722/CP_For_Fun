import os
import re
from collections import defaultdict
from typing import Dict, Set, List
import json
from pathlib import Path

# 常量定义
TARGET_PROBLEMS = set('ABCD')
BIWEEKLY = 'biweekly'
WEEKLY = 'weekly'
CONTEST_LINK = 'https://leetcode.cn/contest/'

# 路径相关常量
SCRIPT_PATH = Path(__file__).resolve()
BASE_DIR = SCRIPT_PATH.parent
REPO_ROOT = BASE_DIR.parent.parent
CODE_DIR = REPO_ROOT / 'CP_leetcode'
OUTPUT_DIR = BASE_DIR.parent / 'leetcode'
OUTPUT_FILE = OUTPUT_DIR / 'contest_todo.txt'
RATINGS_FILE = OUTPUT_DIR / 'leetcode_ratings.json'

# 根据rating设置标签
def get_tag(rating: float) -> str:
    if rating < 2000:
        return '🍰'
    elif rating < 2200:
        return '🛀'
    elif rating < 2400:
        return '🚬'
    elif rating < 2600:
        return '🔪'
    elif rating < 2800:
        return '🔫'
    else:
        return '💣'

def get_unsolved_problems() -> Dict[str, List[str]]:
    unsolved_by_contest = defaultdict(list)
    # 获取题目对应rating
    problem_ratings = get_problem_ratings()
    
    # 遍历文件夹
    for root, dirs, files in os.walk(CODE_DIR):
        # 跳过非叶子目录
        if dirs:
            continue
            
        # 提取比赛信息
        path_components = Path(root).parts
        if len(path_components) < 3:
            continue
            
        contest_id = ''
        if WEEKLY in path_components:
            contest_id += WEEKLY
        if BIWEEKLY in path_components:
            contest_id += BIWEEKLY
        contest_id += '-contest-' + path_components[-1]
        
        # 获取已解决的题目
        solved_problems = {
            problem
            for problem in TARGET_PROBLEMS
            for file in files if problem in file
        }
        # 计算未解决的题目
        unsolved_problems = sorted(TARGET_PROBLEMS - solved_problems)

        if unsolved_problems:
            unsolved_by_contest[contest_id] = unsolved_problems
            print(f"contest_id: {contest_id}", f"unsolved_problems: {unsolved_problems}")
    
    # 写入输出文件
    OUTPUT_DIR.mkdir(exist_ok=True, parents=True)
    print(f"output_path: {OUTPUT_FILE}")
    
    with open(OUTPUT_FILE, 'w', encoding='utf-8') as f:
        f.write("LeetCode Unsolved Problems 💜\n")
        f.write("=" * 50 + "\n\n")

        for contest in sorted(unsolved_by_contest):
            problems = unsolved_by_contest[contest]
            # 构建比赛链接
            contest_link = CONTEST_LINK + contest.replace('_', '-') + '/'
            # 添加比赛标题
            f.write(f"{contest} - {contest_link}\n")
            f.write("-" * 30 + "\n")

            # 输出题目及对应rating
            for problem in problems:
                rating = problem_ratings.get((contest, problem))
                if rating:
                    tag = get_tag(rating)
                    f.write(
                        f"  Problem {problem:<2} - (Rating: {rating:.1f}) - {tag}\n")
                else:
                    f.write(f"  Problem {problem:<2} - Unknown Rating\n")

            # 在比赛之间添加空行
            f.write("\n")
    return unsolved_by_contest


def get_problem_ratings() -> Dict[tuple, float]:
    """获取题目的rating信息
    Returns:
        Dict[tuple, float]: (contest_id, problem_index) -> rating的映射
    """
    problem_ratings = {}
    try:
        with open(RATINGS_FILE, 'r', encoding='utf-8') as f:
            ratings_data = json.load(f)
            for problem in ratings_data:
                # 获取比赛ID（例如：weekly-contest-123）
                contest_id = problem['ContestSlug']
                # 获取题目序号（例如：从'Q4'提取'D'）
                problem_index = chr(
                    ord('A') + int(problem['ProblemIndex'][1]) - 1)
                rating = problem['Rating']

                # 校验比赛ID格式
                if not re.match(r'weekly-contest-\d+|biweekly-contest-\d+',
                                contest_id):
                    print(f"Warning: Invalid contest ID format: {contest_id}")
                    continue
                key = (contest_id, problem_index)
                if key in problem_ratings:
                    print(f"Warning: Duplicate key {key} in ratings data")
                    continue
                problem_ratings[key] = rating

    except FileNotFoundError:
        print(f"Warning: Rating file not found at {RATINGS_FILE}")
    except json.JSONDecodeError:
        print(f"Warning: Invalid JSON format in {RATINGS_FILE}")
    except Exception as e:
        print(f"Warning: Error loading ratings: {e}")

    return problem_ratings


if __name__ == '__main__':
    get_unsolved_problems()
