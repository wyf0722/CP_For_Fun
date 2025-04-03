import os
import re
from collections import defaultdict
from typing import Dict, Set, List
import json

TARGET_PROBLEMS = set('ABCD')
BIWEEKLY = 'biweekly'
WEEKLY = 'weekly'


def get_unsolved_problems() -> Dict[str, List[str]]:
    base_dir = os.path.dirname(os.path.abspath(__file__))
    unsolved_by_contest = defaultdict(list)
    # 获取题目对应rating
    problem_ratings = get_problem_ratings()
    for root, dirs, files in os.walk(base_dir):
        # 跳过非叶子目录和特殊目录
        if dirs or any(skip in root for skip in ['venv', '.git']):
            continue
        # 提取比赛信息
        path_components = root.split(os.path.sep)
        if len(path_components) < 3:
            continue
        contest_id = ''
        if WEEKLY in path_components:
            contest_id += WEEKLY
        if BIWEEKLY in path_components:
            contest_id += BIWEEKLY
        contest_id += '_' + path_components[-1]

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

    # 写入结果文件
    output_path = os.path.join(base_dir, 'contest_todo.txt')
    with open(output_path, 'w') as f:
        f.write("LeetCode Unsolved Problems\n")
        f.write("=" * 50 + "\n\n")

        for contest in sorted(unsolved_by_contest):
            problems = unsolved_by_contest[contest]
            # 添加比赛标题
            f.write(f"{contest}\n")
            f.write("-" * 30 + "\n")

            # 输出题目及对应rating
            for problem in problems:
                rating = problem_ratings.get((contest, problem))
                if rating:
                    f.write(
                        f"  Problem {problem:<2} - (Rating: {rating:.1f})\n")
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
    base_dir = os.path.dirname(os.path.abspath(__file__))
    rating_path = os.path.join(base_dir, 'leetcode_ratings.json')
    problem_ratings = {}
    try:
        with open(rating_path, 'r', encoding='utf-8') as f:
            ratings_data = json.load(f)
            for problem in ratings_data:
                # 获取比赛ID（例如：weekly-contest-123）
                contest_id = problem['ContestSlug']
                # 获取题目序号（例如：从'Q4'提取'D'）
                problem_index = chr(
                    ord('A') + int(problem['ProblemIndex'][1]) - 1)
                rating = problem['Rating']

                # 转换比赛ID格式（例如：weekly-contest-123 -> weekly_123）
                # 使用split方法处理比赛ID
                contest_types = {
                    'biweekly-contest': 'biweekly',
                    'weekly-contest': 'weekly'
                }

                contest_id_converted = False
                for prefix, new_prefix in contest_types.items():
                    if contest_id.startswith(prefix):
                        number = contest_id.split('-')[-1]
                        contest_id = f"{new_prefix}_{number}"
                        contest_id_converted = True
                        break

                if not contest_id_converted:
                    print(
                        f"Warning: Unrecognized contest format: {contest_id}")
                    continue
                key = (contest_id, problem_index)
                if key in problem_ratings:
                    print(f"Warning: Duplicate key {key} in ratings data")
                    continue
                problem_ratings[key] = rating

    except FileNotFoundError:
        print(f"Warning: Rating file not found at {rating_path}")
    except json.JSONDecodeError:
        print(f"Warning: Invalid JSON format in {rating_path}")
    except Exception as e:
        print(f"Warning: Error loading ratings: {e}")

    return problem_ratings


if __name__ == '__main__':
    get_unsolved_problems()
