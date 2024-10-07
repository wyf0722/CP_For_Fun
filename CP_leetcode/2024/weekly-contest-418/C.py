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

class Solution:
    def constructGridLayout(self, n: int, edges: List[List[int]]) -> List[List[int]]:
        g = [[] for _ in range(n)]
        for x, y in edges:
            g[x].append(y)
            g[y].append(x)
        
        deg = [-1] * 5
        for x in range(n):
            deg[len(g[x])] = x 
        
        if deg[1] != -1:
            # 存在度为1的点，只有一列
            row = [deg[1]]
        elif deg[4] == -1:
            # 不存在度为4的点（且不存在度为1的点），只用两列
            x = deg[2]
            for y in g[x]:
                if len(g[y]) == 2:
                    row = [x, y]
                    break
        else:
            # 答案至少三列
            # 第一排度数 233...332
            x = deg[2]
            row = [x]
            pre = x
            x = g[x][0]
            while len(g[x]) == 3:
                row.append(x)
                for y in g[x]:
                    if y != pre and len(g[y]) < 4:
                        # 找到下一个数字
                        pre = x
                        x = y
                        break
            row.append(x)
        
        ans = [[] for _ in range(n // len(row))]
        ans[0] = row
        vis = [False] * n
        for x in row:
            vis[x] = True
        for i in range(1, len(ans)):
            for x in ans[i - 1]:
                for y in g[x]:
                    if not vis[y]:
                        vis[y] = True
                        ans[i].append(y)
                        break
        return ans