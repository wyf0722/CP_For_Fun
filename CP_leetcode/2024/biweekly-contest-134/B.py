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


DEBUG_WITH_COLOR = 1
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
    def maximumPoints(self, v: List[int], x: int) -> int:
        v.sort()
        n = len(v)
        i, j = 0, n - 1
        ans = 0
        while i <= j:
            if x >= v[i]:
               ans += x // v[i]
               x %= v[i]
            else:
                if ans >= 1:
                    x += v[j]
                    j -= 1
                else:
                    break
        return ans 