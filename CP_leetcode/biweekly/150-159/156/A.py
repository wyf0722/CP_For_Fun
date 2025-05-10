class Solution:
    def maxFreqSum(self, s: str) -> int:
        c1 = Counter()
        c2 = Counter()
        for x in s:
            if x in 'aeiou':
                c1[x] += 1
            else:
                c2[x] += 1
        v1 = max(c1.values()) if c1 else 0
        v2 = max(c2.values()) if c2 else 0
        return v1 + v2