from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache
from heapq import heapify, heappop, heappush
from itertools import pairwise, permutations
from math import comb, gcd, inf, lcm, log2, perm
from typing import List

from sortedcontainers import SortedDict, SortedList, SortedSet

"""
stuff you should look for
int overflow, array bounds
special cases (n=1?)
do smth instead of nothing and stay organized
WRITE STUFF DOWN
DON'T GET STUCK ON ONE APPROACH
"""
"""
testcases = [
    [[2,3,0,0,2], 4, 'd'],
]

s = Solution()
func_name = dir(s)[-1]
func = getattr(s, func_name)

for args in testcases:
    print(func(*args))
""" 

