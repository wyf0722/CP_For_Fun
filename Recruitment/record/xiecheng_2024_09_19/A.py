standard_input, packages, output_together = 1, 1, 1
dfs, hashing, read_from_file = 0, 0, 0
de = 1
 
if 1:
 
    if standard_input:
        import io, os, sys
        input = lambda: sys.stdin.readline().strip()
 
        inf = float('inf')
 
        def I():
            return input()
        
        def II():
            return int(input())
 
        def MII():
            return map(int, input().split())
 
        def LI():
            return list(input().split())
 
        def LII():
            return list(map(int, input().split()))
 
        def LFI():
            return list(map(float, input().split()))
 
        def GMI():
            return map(lambda x: int(x) - 1, input().split())
 
        def LGMI():
            return list(map(lambda x: int(x) - 1, input().split()))
 
    if packages:
        from io import BytesIO, IOBase
        import math
 
        import random
        import os
 
        import bisect
        import typing
        from collections import Counter, defaultdict, deque
        from copy import deepcopy
        from functools import cmp_to_key, lru_cache, reduce
        from heapq import heapify, heappop, heappush, heappushpop, nlargest, nsmallest
        from itertools import accumulate, combinations, permutations, count, product
        from operator import add, iand, ior, itemgetter, mul, xor
        from string import ascii_lowercase, ascii_uppercase, ascii_letters
        from typing import *
        BUFSIZE = 4096
 
    if output_together:
        class FastIO(IOBase):
            newlines = 0
 
            def __init__(self, file):
                self._fd = file.fileno()
                self.buffer = BytesIO()
                self.writable = "x" in file.mode or "r" not in file.mode
                self.write = self.buffer.write if self.writable else None
 
            def read(self):
                while True:
                    b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
                    if not b:
                        break
                    ptr = self.buffer.tell()
                    self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
                self.newlines = 0
                return self.buffer.read()
 
            def readline(self):
                while self.newlines == 0:
                    b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
                    self.newlines = b.count(b"\n") + (not b)
                    ptr = self.buffer.tell()
                    self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
                self.newlines -= 1
                return self.buffer.readline()
 
            def flush(self):
                if self.writable:
                    os.write(self._fd, self.buffer.getvalue())
                    self.buffer.truncate(0), self.buffer.seek(0)
 
        class IOWrapper(IOBase):
            def __init__(self, file):
                self.buffer = FastIO(file)
                self.flush = self.buffer.flush
                self.writable = self.buffer.writable
                self.write = lambda s: self.buffer.write(s.encode("ascii"))
                self.read = lambda: self.buffer.read().decode("ascii")
                self.readline = lambda: self.buffer.readline().decode("ascii")
 
        sys.stdout = IOWrapper(sys.stdout)
 
    if dfs:
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
 
    if hashing:
        RANDOM = random.getrandbits(20)
        class Wrapper(int):
            def __init__(self, x):
                int.__init__(x)
 
            def __hash__(self):
                return super(Wrapper, self).__hash__() ^ RANDOM
 
    if read_from_file:
        file = open("input.txt", "r").readline().strip()[1:-1]
        fin = open(file, 'r')
        input = lambda: fin.readline().strip()
        output_file = open("output.txt", "w")
        def fprint(*args, **kwargs):
            print(*args, **kwargs, file=output_file)
 
    if de:
        def debug(*args, **kwargs):
            print('\033[92m', end='')
            print(*args, **kwargs)
            print('\033[0m', end='')

#
#   █████▒█    ██  ▄████▄   ██ ▄█▀       ██████╗ ██╗   ██╗ ██████╗
# ▓██   ▒ ██  ▓██▒▒██▀ ▀█   ██▄█▒        ██╔══██╗██║   ██║██╔════╝
# ▒████ ░▓██  ▒██░▒▓█    ▄ ▓███▄░        ██████╔╝██║   ██║██║  ███╗
# ░▓█▒  ░▓▓█  ░██░▒▓▓▄ ▄██▒▓██ █▄        ██╔══██╗██║   ██║██║   ██║
# ░▒█░   ▒▒█████▓ ▒ ▓███▀ ░▒██▒ █▄       ██████╔╝╚██████╔╝╚██████╔╝
#  ▒ ░   ░▒▓▒ ▒ ▒ ░ ░▒ ▒  ░▒ ▒▒ ▓▒       ╚═════╝  ╚═════╝  ╚═════╝
#  ░     ░░▒░ ░ ░   ░  ▒   ░ ░▒ ▒░
#  ░ ░    ░░░ ░ ░ ░        ░ ░░ ░
#           ░     ░ ░      ░  ░
MULTITEST = 1
MOD = 1_000_000_007
def main():
    n, m, k = MII()
    x = 0
    y = 0
    ans = 0

    def f(x:int, y:int) -> int:
        return x * m + y

    if n != 1:
        if k <= n - 1:
            ans += (f(1, 0) + f(k, 0)) * k // 2
            k = 0
        else:
            ans += (f(1, 0) + f(n - 1, 0)) * (n - 1) // 2
            k -= n - 1
    if k == 0:
        print(ans)
        return

    if m != 1:
        if k <= m - 1:
            ans += (f(n - 1, 1) + f(n - 1, k)) * k // 2
            k = 0
        else:
            ans += (f(n - 1, 1) + f(n - 1, m - 1)) * (m - 1) // 2
            k -= m - 1
    if k == 0:
        print(ans)
        return
    if k > 0:
        node1 = f(n - 1, m - 1)
        node2 = f(n - 2, m - 1) if m == 1 else f(n - 1, m - 2)
        ans += (k // 2) * (node1 + node2)
        if k & 1:
            ans += node2
    print(ans)


t = 1
if MULTITEST:
    t = II()
for _ in range(t):
    main()