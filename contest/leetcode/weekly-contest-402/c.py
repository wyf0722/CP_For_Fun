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
    def maximumTotalDamage(self, power: List[int]) -> int:
        cnt = defaultdict(int)
        for i in power:
            cnt[i] += i
        infos = list(sorted(cnt.items()))
        n = len(infos)
        dp = [0] * (n + 1)
        mx = [0] * (n + 1)
        ans = 0
        for i in range(n):
            v, c = infos[i][0], infos[i][1]
            if i - 1 >= 0 and infos[i - 1][0] < v - 2:
                dp[i + 1] = max(dp[i + 1], dp[i] + c)
            if i - 2 >= 0 and infos[i - 2][0] < v - 2:
                dp[i + 1] = max(dp[i + 1], dp[i - 1] + c)
            dp[i + 1] = max(dp[i + 1], mx[max(0, i - 2)] + c)
            mx[i + 1] = max(mx[i], dp[i + 1])
        return mx[-1]