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
    def maximumDetonation(self, bs: List[List[int]]) -> int:
        n = len(bs)
        g = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(n):
                if i == j:
                    continue
                if (bs[i][0] - bs[j][0]) ** 2 + (bs[i][1] - bs[j][1]) ** 2 <= bs[i][2] ** 2:
                    g[i][j] = 1
        ans = 1
        for i in range(n):
            vis = [0] * n
            vis[i] = 1
            q = deque()
            q.append(i)
            cur = 1
            while q:
                x = q.popleft()
                for y in range(n):
                    if vis[y]:
                        continue
                    vis[y] = 1
                    q.append(y)
                    cur += 1
            ans = max(ans, cur)
        return ans
                