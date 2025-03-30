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

def calc(s: str, t: str) -> int:
    n, m = len(s), len(t)
    lcp = [0] * (m + 1)
    mx = [0] * n
    mx_p = [0] * (n + 1)

    for i in range(n - 1, -1, -1):
        new_lcp = [0] * (m + 1)
        for j in range(m - 1, -1, -1):
            if s[i] == t[j]:
                new_lcp[j] = lcp[j + 1] + 1
                mx[i] = max(mx[i], new_lcp[j])
        lcp = new_lcp

    for i in range(2 * n - 1):
        l, r = i // 2, (i + 1) // 2
        while l >= 0 and r < n and s[l] == s[r]:
            l -= 1
            r += 1
        mx_p[l + 1] = max(mx_p[l + 1], r - l - 1)

    ans = 0
    for i in range(n):
        ans = max(ans, mx_p[i])
        for j in range(i, i + mx[i]):
            ans = max(ans, (j - i + 1) * 2 + mx_p[j + 1])

    return ans

class Solution:
    def longestPalindrome(self, s: str, t: str) -> int:
        t = t[::-1]
        return max(calc(s, t), calc(t, s))
