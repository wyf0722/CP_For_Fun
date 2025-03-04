import os
import random
import sys
from typing import *
from collections import defaultdict, Counter, deque
from functools import cache, reduce
from itertools import pairwise, combinations, permutations, groupby, accumulate
from bisect import bisect_left, bisect_right, insort_left, insort_right
from heapq import *
from math import gcd, lcm, isqrt
from operator import add, sub, mul, floordiv, truediv, and_, or_, xor

from types import GeneratorType


def bootstrap(f, stack=[]):

    def wrappedfunc(*args, **kwargs):
        if stack:
            return f(*args, **kwargs)
        else:
            to = f(*args, **kwargs)
            while True:
                if type(to) is GeneratorType:
                    stack.append(to)
                    to = next(to)
                else:
                    stack.pop()
                    if not stack:
                        break
                    to = stack[-1].send(to)
            return to

    return wrappedfunc


input = sys.stdin.readline
output = lambda x: sys.stdout.write(str(x) + "\n")
outputL = lambda x: sys.stdout.write(" ".join(map(str, x)) + "\n")

printerr = lambda *args, **kwargs: print(
    "\u001B[31m", *args, "\u001B[0m", file=sys.stderr, **kwargs)

I = lambda: input().rstrip("\n")
II = lambda: int(input())
MII = lambda: map(int, input().split())
LMII = lambda: list(MII())
TMII = lambda: tuple(MII())
LI = lambda: list(I())
LSI = lambda: list(map(int, I()))


dirs = (1, 1), (1, -1), (-1, -1), (-1, 1)
class Solution:
    def lenOfVDiagonal(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        @cache
        def f(i:int, j:int, d:int, turn:bool, target:int) -> int:
            if not (0 <= i < m and 0 <= j < n) or grid[i][j] != target:
                return 0
            # 继续沿着该方向
            r = f(i + dirs[d][0], j + dirs[d][1], d, turn, 2 - target)
            # 拐
            if not turn:
                nd = (d + 1) % 4
                r = max(r, f(i + dirs[nd][0], j + dirs[nd][1], nd, True, 2 - target))
            return r + 1
        
        ans = 0
        for i, row in enumerate(grid):
            for j, val in enumerate(row):
                if val == 1:
                    for d in range(4):
                        ans = max(ans, f(i + dirs[d][0], j + dirs[d][1], d, False, 2) + 1)
        
        return ans