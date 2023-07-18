from typing import List
from functools import cache
from collections import Counter
import logging

a = [i for i in range(10)]
b = [chr(i) for i in range(97, 107)]

print(a)
print(b)

c = zip(a, b)
for index, (i, j) in enumerate(c):
    print(index, i, j)

cc = Counter()

cc['a'] += 1
print(cc)