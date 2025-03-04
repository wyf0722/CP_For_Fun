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
    def countMentions(self, numberOfUsers: int, events: List[List[str]]) -> List[int]:
        infos = [-1] * numberOfUsers
        ans = [0] * numberOfUsers
        events.sort(key=lambda x : (int(x[1]), 1 if x[0] == "MESSAGE" else 0))
        for flag, t, s in events:
            timestamp = int(t)
            if flag == 'MESSAGE':
                if s == 'ALL':
                    for i in range(numberOfUsers):
                        ans[i] += 1
                elif s == 'HERE':
                    for i, online_t in enumerate(infos):
                        if online_t <= timestamp:
                            ans[i] += 1
                else:
                    ids = [int(id[2:]) for id in list(s.split(' '))]
                    for id in ids:
                        ans[id] += 1
            else:
                infos[int(s)] = timestamp + 60
        return ans