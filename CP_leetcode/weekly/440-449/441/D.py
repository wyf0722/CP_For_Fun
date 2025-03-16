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
    def beautifulNumbers(self, l: int, r: int) -> int:
        def f(num:int) -> int:
            x = str(num)
            n = len(x)
            
            @cache
            def dp(i:int, is_limit, is_num, s, p) -> int:
                if i == n:
                    return is_num and s != 0 and p % s == 0
                # 不填
                r = 0
                if not is_num:
                    r += dp(i + 1, False, is_num, s, p)
                # 填
                lo = 0 if is_num else 1
                hi = 9 if not is_limit else int(x[i])
                for d in range(lo, hi + 1):
                    r += dp(i + 1, is_limit and d == hi, True, s + d, p * d)
                return r
            return dp(0, True, False, 0, 1)
        return f(r) - f(l - 1)
    
'''
无is_num版本，注意未填数字的时候乘积的处理逻辑
'''
# class Solution:
#     def beautifulNumbers(self, l: int, r: int) -> int:
#         def f(num:int) -> int:
#             x = str(num)
#             n = len(x)
            
#             @cache
#             def dp(i:int, is_limit, s, p) -> int:
#                 if i == n:
#                     return s != 0 and p % s == 0
#                 r = 0
#                 lo = 0
#                 hi = 9 if not is_limit else int(x[i])
#                 for d in range(lo, hi + 1):
#                     if d == 0 and s == 0:
#                         r += dp(i + 1, is_limit and d == hi, 0, 1)
#                     else:
#                         r += dp(i + 1, is_limit and d == hi, s + d, p * d)
#                 return r
#             return dp(0, True, 0, 1)
#         return f(r) - f(l - 1)