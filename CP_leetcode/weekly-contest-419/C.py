import inspect
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, cmp_to_key, lru_cache, reduce
from heapq import heapify, heappop, heappush, heappushpop, nlargest, nsmallest
from itertools import accumulate, count, pairwise, permutations
from math import comb, gcd, inf, lcm, log2, perm, sqrt
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

MOD = 1_000_000_007
class Solution:
    def countWinningSequences(self, s: str) -> int:
        n = len(s)
        idx = {c : i for i, c in enumerate("FWE")}
        @cache
        def f(i:int, pre:int, d:int) -> int:
            # 必败
            if n - i + d < 0:
                return 0
            # 必胜
            if n - i < d:
                return pow(2, n - i, MOD)
            if i == n:
                return 1 if d > 0 else 0
            r = 0
            for cur in range(3):
                if cur == pre:
                    continue
                score = 0
                if cur == idx[s[i]]:
                    score = 0
                elif (idx[s[i]] + 1) % 3 == cur:
                    score = 1
                else:
                    score = -1
                r += f(i + 1, cur, d + score)
            return r % MOD
        
        return f(0, -1, 0)