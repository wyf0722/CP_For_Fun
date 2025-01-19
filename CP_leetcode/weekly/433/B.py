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

class Combinatorics:
    def __init__(self, n, mod):
        assert mod > n
        self.n = n + 10
        self.mod = mod

        self.perm = [1]
        self.rev = [1]
        self.inv = [0]
        self.fault = [0]

        self.build_perm()
        self.build_rev()
        self.build_inv()
        self.build_fault()
        return

    def build_perm(self):
        self.perm = [1] * (self.n + 1)  # (i!) % mod
        for i in range(1, self.n + 1):
            self.perm[i] = self.perm[i - 1] * i % self.mod
        return

    def build_rev(self):
        self.rev = [1] * (self.n + 1)  # pow(i!, -1, mod)
        self.rev[-1] = pow(self.perm[-1], -1, self.mod)  # GcdLike().mod_reverse(self.perm[-1], self.mod)
        for i in range(self.n - 1, 0, -1):
            self.rev[i] = (self.rev[i + 1] * (i + 1) % self.mod)  # pow(i!, -1, mod)
        return

    def build_inv(self):
        self.inv = [0] * (self.n + 1)  # pow(i, -1, mod)
        self.inv[1] = 1
        for i in range(2, self.n + 1):
            self.inv[i] = (self.mod - self.mod // i) * self.inv[self.mod % i] % self.mod
        return

    def build_fault(self):
        self.fault = [0] * (self.n + 1)  # fault permutation
        self.fault[0] = 1
        self.fault[2] = 1
        for i in range(3, self.n + 1):
            self.fault[i] = (i - 1) * (self.fault[i - 1] + self.fault[i - 2])
            self.fault[i] %= self.mod
        return

    def comb(self, a, b):
        if a < b:
            return 0
        res = self.perm[a] * self.rev[b] * self.rev[a - b]  # comb(a, b) % mod = (a!/(b!(a-b)!)) % mod
        return res % self.mod

    def factorial(self, a):
        res = self.perm[a]  # (a!) % mod
        return res % self.mod

    def inverse(self, n):
        res = self.perm[n - 1] * self.rev[n] % self.mod  # pow(n, -1, mod)
        return res

    def catalan(self, n):
        res = (self.comb(2 * n, n) - self.comb(2 * n, n - 1)) % self.mod
        return res

MOD = 1_000_000_007
Comb = Combinatorics(100000, MOD)
class Solution:
    def minMaxSums(self, nums: List[int], k: int) -> int:
        ans = 0
        n = len(nums)
        nums.sort()
        for i, x in enumerate(nums):
            as_max = sum(Comb.comb(i, j) for j in range(min(k, i + 1)))
            as_min = sum(Comb.comb(n - 1 - i, j) for j in range(min(k, n - 1 - i + 1)))
            ans += x * (as_max + as_min)
            ans %= MOD
        return ans
