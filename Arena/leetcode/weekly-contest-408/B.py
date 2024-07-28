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

class PrimeFactor:
    def __init__(self, n):
        self.n = n
        # calculate the minimum prime factor for all numbers from 1 to self.n
        self.min_prime = [0] * (self.n + 1)
        # determine whether all numbers from 1 to self.n are prime numbers
        self.is_prime = [0] * (self.n + 1)
        # calculate the prime factorization of all numbers from 1 to self.n
        self.prime_factor = [[] for _ in range(self.n + 1)]
        # calculate all factors of all numbers from 1 to self.n, including 1 and the number itself
        self.all_factor = [[], [1]] + [[1, i] for i in range(2, self.n + 1)]
        self.build()
        return

    def build(self):

        # complexity is O(nlogn)
        for i in range(2, self.n + 1):
            if not self.min_prime[i]:
                self.is_prime[i] = 1
                self.min_prime[i] = i
                for j in range(i * i, self.n + 1, i):
                    if not self.min_prime[j]:
                        self.min_prime[j] = i

        # complexity is O(nlogn)
        for num in range(2, self.n + 1):
            i = num
            while num > 1:
                p = self.min_prime[num]
                cnt = 0
                while num % p == 0:
                    num //= p
                    cnt += 1
                self.prime_factor[i].append((p, cnt))

        # complexity is O(nlogn)
        for i in range(2, self.n + 1):
            x = i
            while x * i <= self.n:
                self.all_factor[x * i].append(i)
                if i != x:
                    self.all_factor[x * i].append(x)
                x += 1
        for i in range(self.n + 1):
            self.all_factor[i].sort()
        return

    def comb(self, a, b):
        # Use prime factor decomposition to solve the values of combinatorial mathematics
        # and prime factor decomposition O ((a+b) log (a+b))
        cnt = defaultdict(int)
        for i in range(1, a + 1):  # a!
            for num, y in self.prime_factor[i]:
                cnt[num] += y
        for i in range(1, b + 1):  # b!
            for num, y in self.prime_factor[i]:
                cnt[num] -= y
        for i in range(1, a - b + 1):  # (a-b)!
            for num, y in self.prime_factor[i]:
                cnt[num] -= y
        ans = 1
        for w in cnt:
            ans *= w ** cnt[w]
        return ans

    def get_prime_numbers(self):
        return [i for i in range(1, self.n + 1) if self.is_prime[i]]

primes = PrimeFactor(100000).get_prime_numbers()
n = len(primes)
class Solution:
    def nonSpecialCount(self, l: int, r: int) -> int:
        def f(x:int) -> int:
            lo, hi = -1, n
            while lo + 1 < hi:
                mid = (lo + hi) // 2
                if primes[mid] * primes[mid] <= x:
                    lo = mid
                else:
                    hi = mid
            return lo
        return r - l + 1 - (f(r) - f(l - 1))