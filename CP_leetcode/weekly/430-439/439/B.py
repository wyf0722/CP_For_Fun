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

class Solution:
    def longestPalindromicSubsequence(self, s: str, k: int) -> int:
        n = len(s)

        @cache
        def f(i:int, j:int, ops:int) -> int:
            if i == j:
                return 1
            if i > j:
                return 0
            if s[i] == s[j]:
                return f(i + 1, j - 1, ops) + 2
            r = f(i + 1, j - 1, ops)
            r = max(r, f(i + 1, j, ops))
            r = max(r, f(i, j - 1, ops))
            cur_op = abs(ord(s[i]) - ord(s[j]))
            cur_op = min(cur_op, 26 - cur_op)
            if ops >= cur_op:
                r = max(r, f(i + 1, j - 1, ops - cur_op) + 2)
            return r
        
        return f(0, n - 1, k)