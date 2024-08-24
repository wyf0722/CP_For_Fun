import inspect
import sys
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

input = lambda: sys.stdin.readline().strip()
MOD = int(1e9 + 7)
dx = [0, 1, 0, -1]
dy = [1, 0, -1, 0]


DEBUG_WITH_COLOR = 0
def debug(*args, **kwargs):
    stack_info = inspect.stack()[1]  # [1] 表示获取调用栈中的第二个帧（第一个帧是当前函数）
    line_number = stack_info.lineno
    # 定义ANSI颜色代码
    COLOR = '\033[95m'
    RESET = '\033[0m'
    # 打印调试信息
    if DEBUG_WITH_COLOR:
        print(f"{COLOR}Line {line_number}{RESET}: ", *args, **kwargs)
    else:
        print(f"Line {line_number}: ", *args, **kwargs)


'''
arr1[i] = j
arr2[i] = nums[i] - j

arr1[i - 1] = k
arr2[i - 1] = nums[i - 1] - k
约束：
k <= j && nums[i - 1] - k >= nums[i] - j

k <= j && k <= nums[i - 1] - nums[i] + j
'''
class Solution:
    def countOfPairs(self, nums: List[int]) -> int:
        n = len(nums)
        
        dp = [[0] * 1001 for _ in range(n)]
        for j in range(nums[0] + 1):
            dp[0][j] = 1
        for i in range(1, n):
            s = dp[i - 1]
            for j in range(1, 1001):
                s[j] += s[j - 1]
            for j in range(nums[i] + 1):
                limit = min(j, nums[i - 1] - nums[i] + j)
                dp[i][j] = s[limit] % MOD if limit >= 0 else 0
        return sum(dp[-1][:nums[-1] + 1])
        
