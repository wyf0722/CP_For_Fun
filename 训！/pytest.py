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

LOCAL_DEBUG = 1
if LOCAL_DEBUG:

    def debug(*args, **kwargs):
        print("\033[35m", end="")
        print(*args, **kwargs)
        print("\033[0m", end="")


# 𝓽𝓱𝓮 𝓼𝓸𝓵𝓾𝓽𝓲𝓸𝓷 𝓸𝓯 𝔀𝔂𝓯0722

class Solution:
    def maximumLength(self, nums: List[int], k: int) -> int:
        n = len(nums)
        dp = [[1] * (k + 1) for _ in range(n + 1)]
        ans = 0
        for i in range(n):
            for j in range(i):
                for kk in range(k + 1):
                    if nums[i] == nums[j]:
                        dp[i][kk] = max(dp[i][kk], dp[j][k] + 1)
                    if nums[i] != nums[j] and kk:
                        dp[i][kk] = max(dp[i][kk], dp[j][kk - 1] + 1)
                    ans = max(ans, dp[i][kk])
        return ans