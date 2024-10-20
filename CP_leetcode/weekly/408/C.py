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
    def minFlips(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        ans = 0
        for i in range(m // 2):
            for j in range(n // 2):
                c1 = grid[i][j] + grid[m - 1 - i][j] + grid[i][n - 1 - j] + grid[m - 1 - i][n - 1 - j]
                ans += min(c1, 4 - c1)
        if m & 1 and n & 1:
            ans += grid[m // 2][n // 2]
        dif, c1 = 0, 0
        if m % 2:
            for j in range(n // 2):
                if grid[m // 2][j] != grid[m // 2][n - 1 - j]:
                    dif += 1
                else:
                    c1 += grid[m // 2][j] * 2
        if n % 2:
            for i in range(m // 2):
                if grid[i][n // 2] != grid[m - 1 - i][n // 2]:
                    dif += 1
                else:
                    c1 += grid[i][n // 2] * 2
        if c1 % 4 == 0:
            return ans + dif
        # 余数只可能为2
        assert c1 % 4 == 2
        if dif:
            return ans + dif
        return ans + 2