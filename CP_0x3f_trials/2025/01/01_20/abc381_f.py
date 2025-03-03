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

fmax = lambda x, y: x if x > y else y
fmin = lambda x, y: x if x < y else y
MULTITEST = 0
MOD = 1_000_000_007
def main():
    n = II()
    nums = list(map(lambda x: int(x) - 1, input().split()))

    next_pos = [[n] * (n + 1) for _ in range(20)]
    for i in range(n - 1, -1, -1):
        for j in range(20):
            next_pos[j][i] = next_pos[j][i + 1]
        next_pos[nums[i]][i] = i

    dp = [n + 1] * (1 << 20)
    dp[0] = 0

    for msk in range(1 << 20):
        for j in range(20):
            if msk >> j & 1 == 0:
                nmsk = msk | (1 << j)
                if dp[msk] >= n: continue
                p = next_pos[j][dp[msk]]
                if p < n:
                    p = next_pos[j][p + 1]
                    if p < n and p < dp[nmsk]:
                        dp[nmsk] = p + 1

    ans = 0
    for i in range(1 << 20):
        if dp[i] <= n:
            ans = fmax(ans, i.bit_count())

    print(ans * 2)

T = 1
if MULTITEST:
    T = II()
for _ in range(T):
    main()