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

'''
dp[i][j] = max(dp[i - 1][k] - abs(j - k)) + points[i][j]
1. j >= k -> max(dp[i - 1][k] + k) + points[i][j] - j
2. j <= k  -> max(dp[i - 1][k] - k) + points[i][j] + j
'''

MOD = 10**9 + 7
class Solution:
    def numOfWays(self, n: int) -> int:
        # 121 -> 212 213 232 312 313  a -> 3a 2b
        # 123 -> 212 231 232 312      b -> 2a 2b
        a = 6
        b = 6
        cur = 1
        for i in range(n):
            cur *= (a + b)
            a, b = 3 * a + 2 * b, 2 * a + 2 * b
        return cur