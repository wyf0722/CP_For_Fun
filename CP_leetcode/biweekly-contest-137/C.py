import inspect
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, cmp_to_key, lru_cache, reduce
from heapq import heapify, heappop, heappush, heappushpop, nlargest, nsmallest
from itertools import accumulate, count, pairwise, permutations
from math import comb, gcd, inf, lcm, log2, perm
from operator import add, iand, ior, itemgetter, mul, xor
from string import ascii_letters, ascii_lowercase, ascii_uppercase
from typing import List

from sortedcontainers import SortedDict, SortedList, SortedSet

input = lambda: sys.stdin.readline().strip()
MOD = int(1e9 + 7)
dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]


DEBUG_WITH_COLOR = 0
def debug(*args, **kwargs):
    stack_info = inspect.stack()[1]  # [1] 表示获取调用栈中的第二个帧（第一个帧是当前函数）
    line_number = stack_info.lineno
    # 定义ANSI颜色代码
    COLOR = '\033[95m'
    RESET = '\033[0m'
    # 打印调试信息
    if DEBUG_WITH_COLOR:
        print(f"{COLOR}Line {line_number}{RESET}: ", *args, **kwargs)
    else:
        print(f"Line {line_number}: ", *args, **kwargs)

class Solution:
    def maximumValueSum(self, board: List[List[int]]) -> int:
        m, n = len(board), len(board[0])
        infos = []
        for i in range(m):
            row_info = [(board[i][j], j) for j in range(n)]
            infos.append(sorted(row_info, reverse=True)[:3])
        ans = -inf
        for r1 in range(m - 2):
            for r2 in range(r1 + 1, m - 1):
                for r3 in range(r2 + 1, m):
                    for id1 in range(3):
                        for id2 in range(3):
                            for id3 in range(3):
                                val1, c1 = infos[r1][id1]
                                val2, c2 = infos[r2][id2]
                                val3, c3 = infos[r3][id3]
                                if c1 != c2 and c1 != c3 and c2 != c3:
                                    ans = max(ans, val1 + val2 + val3)
        return ans