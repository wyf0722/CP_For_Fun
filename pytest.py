from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache
from heapq import heapify, heappop, heappush
from itertools import pairwise, permutations
from math import gcd, inf, lcm, comb, log2
from typing import List
<<<<<<< HEAD
  

=======


class DSU:
    def __init__(self, n, size=None):
        self.parent = list(range(n))
        self.size = [1] * n if size is None else size

    def find(self, a):
        a = self.parent[a]
        acopy = a
        while a != self.parent[a]:
            a = self.parent[a]
        while acopy != a:
            self.parent[acopy], acopy = a, self.parent[acopy]
        return a

    def merge(self, a, b):
        pa, pb = self.find(a), self.find(b)
        if pa == pb: return False
        self.parent[pb] = pa
        self.size[pa] += self.size[pb]
        return True

    def getSize(self, a):
        return self.size[self.find(a)]
    
class Solution:
    def minScore(self, n: int, roads: List[List[int]]) -> int:
        ans = 100000
        dsu = DSU(n + 1)
        for x, y, d in roads:
            dsu.merge(x, y)
        for x, y, d in roads:
            if dsu.same(x, 1):
                ans = min(ans, d)
        return ans
>>>>>>> b28f0f037bd0fe16eb7416ccf5501529b0ac4e34
