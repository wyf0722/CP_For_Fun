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

inf = 10**12


class Solution:

    def minCost(self, n: int, cost: List[List[int]]) -> int:
        dp = [[[inf] * 3 for _ in range(3)] for _ in range(n // 2)]
        for left in range(3):
            for right in range(3):
                if left != right:
                    dp[0][left][right] = cost[0][left] + cost[n - 1][right]

        for i in range(1, n // 2):
            for left in range(3):
                for right in range(3):
                    if left == right: continue
                    for pre_left in range(3):
                        if left == pre_left: continue
                        for pre_right in range(3):
                            if pre_left == pre_right: continue
                            if right == pre_right: continue
                            dp[i][left][right] = min(
                                dp[i][left][right],
                                dp[i - 1][pre_left][pre_right] + cost[i][left] + cost[n - 1 - i][right])
        ans = inf
        for left in range(3):
            for right in range(3):
                if left != right:
                    ans = min(ans, dp[-1][left][right])
        return ans
