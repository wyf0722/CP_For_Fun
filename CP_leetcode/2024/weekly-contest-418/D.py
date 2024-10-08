import inspect
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, cmp_to_key, lru_cache, reduce
from heapq import heapify, heappop, heappush, heappushpop, nlargest, nsmallest
from itertools import accumulate, count, pairwise, permutations
from math import comb, gcd, inf, lcm, log2, perm, sqrt
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
cnt_gcd[i] = C(cnt[k * i], 2) - cnt_gcd[i * 2] - cnt_gcd[i * 3] - ....
倒序递推
'''
class Solution:
    def gcdValues(self, nums: List[int], queries: List[int]) -> List[int]:
        mx = max(nums)
        cnt_x = [0] * (mx + 1)
        for x in nums:
            cnt_x[x] += 1
        
        cnt_gcd = [0] * (mx + 1)
        for i in range(mx, 0, -1):
            c = 0
            for j in range(i, mx + 1, i):
                c += cnt_x[j]
                cnt_gcd[i] -= cnt_gcd[j]
            cnt_gcd[i] += c * (c - 1) // 2

        pre_sum = list(accumulate(cnt_gcd))
        ans = []
        for q in queries:
            r = bisect_right(pre_sum, q)
            ans.append(r)
        return ans
