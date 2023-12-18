from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache
from heapq import heapify, heappop, heappush
from itertools import accumulate, pairwise, permutations, count
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

class Solution:
    def minOperations(self, nums1: List[int], nums2: List[int]) -> int:
        s1 = sum(nums1)
        s2 = sum(nums2)
        if s1 == s2:
            return 0
        a = []
        if s1 > s2:
            for x in nums1:
                if x != 1:
                    a.append(x - 1)
            for x in nums2:
                if x != 6:
                    a.append(6 - x)
        else:
            for x in nums2:
                if x != 1:
                    a.append(x - 1)
            for x in nums1:
                if x != 6:
                    a.append(6 - x)
        
        a.sort(reverse=True)
        d = abs(s1 - s2)
        ans = 0
        for x in a:
            d -= x
            ans += 1
            if d <= 0:
                return ans
        return -1