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

import typing


class Fenwick:
    '''Reference: https://en.wikipedia.org/wiki/Fenwick_tree'''

    def __init__(self, n: int = 0) -> None:
        self._n = n
        self.data = [0] * n

    def add(self, p: int, x: typing.Any) -> None:
        assert 0 <= p < self._n

        p += 1
        while p <= self._n:
            self.data[p - 1] += x
            p += p & -p

    def rangeSum(self, left: int, right: int) -> typing.Any:
        assert 0 <= left <= right <= self._n

        return self.sum(right) - self.sum(left)

    def sum(self, r: int) -> typing.Any:
        s = 0
        while r > 0:
            s += self.data[r - 1]
            r -= r & -r

        return s

class Solution:
    def countOfPeaks(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        n = len(nums)
        fen = Fenwick(n)

        def check(i:int, val:int) -> None:
            if nums[i - 1] < nums[i] and nums[i] > nums[i + 1]:
                fen.add(i, val)
        for i in range(1, n - 1):
            check(i, 1)
        
        ans = []
        for op, i, val in queries:
            if op == 1:
                if i + 1 >= val:
                    ans.append(0)
                else:
                    ans.append(fen.rangeSum(i + 1, val))
            else:
                for j in range(max(i - 1, 1), min(i + 2, n - 1)):
                    check(j, -1)
                nums[i] = val
                for j in range(max(i - 1, 1), min(i + 2, n - 1)):
                    check(j, 1)
        return ans
