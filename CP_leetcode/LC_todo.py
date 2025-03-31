import os
import re
from collections import defaultdict
from typing import Dict, Set, List

TARGET_PROBLEMS = set('ABCD')


def get_unsolved_problems() -> Dict[str, List[str]]:
    base_dir = os.path.dirname(os.path.abspath(__file__))
    unsolved_by_contest = defaultdict(list)

    for root, dirs, files in os.walk(base_dir):
        # 跳过非叶子目录和特殊目录
        if dirs or any(skip in root for skip in ['venv', '.git']):
            continue
        # 提取比赛信息
        path_components = root.split(os.path.sep)
        if len(path_components) < 3:
            continue
        contest_id = f"{path_components[-3]}_{path_components[-1]}"
        # print(contest_id, files)

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
        for contest in sorted(unsolved_by_contest):
            problems = unsolved_by_contest[contest]
            f.write(f'{contest}: {{{", ".join(problems)}}}\n')

    return unsolved_by_contest


if __name__ == '__main__':
    get_unsolved_problems()
