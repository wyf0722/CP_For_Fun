standard_input, packages, output_together = 1, 1, 0
dfs, hashing, read_from_file = 0, 0, 0
de = 1

if 1:

    if standard_input:
        import io, os, sys
        input = lambda: sys.stdin.readline().strip()

        import math
        inf = math.inf

        def I():
            return input()

        def II():
            return int(input())

        def MII():
            return map(int, input().split())

        def LI():
            return input().split()

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

        import random
        import os

        import bisect
        import typing
        from collections import Counter, defaultdict, deque
        from copy import deepcopy
        from functools import cmp_to_key, lru_cache, reduce
        from heapq import merge, heapify, heappop, heappush, heappushpop, nlargest, nsmallest
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

        def bootstrap(f, stk=[]):
            def wrappedfunc(*args, **kwargs):
                if stk:
                    return f(*args, **kwargs)
                else:
                    to = f(*args, **kwargs)
                    while True:
                        if type(to) is GeneratorType:
                            stk.append(to)
                            to = next(to)
                        else:
                            stk.pop()
                            if not stk:
                                break
                            to = stk[-1].send(to)
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

    fmax = lambda x, y: x if x > y else y
    fmin = lambda x, y: x if x < y else y

    class lst_lst:
        def __init__(self, n) -> None:
            self.n = n
            self.pre = []
            self.cur = []
            self.lst = [-1] * n

        def append(self, i, j):
            self.pre.append(self.lst[i])
            self.lst[i] = len(self.cur)
            self.cur.append(j)

        def iterate(self, i):
            tmp = self.lst[i]
            while tmp != -1:
                yield self.cur[tmp]
                tmp = self.pre[tmp]
'''
> File Name: D.py
> Author: Wu YiFan
> Github: https://github.com/wyf0722
> Mail: wyf0722chosen@gmail.com
> Created Time: 2026-03-21 23:54
'''

class Solution:
    # ---------------- 状态常量定义（避免魔数） ----------------
    # 初始状态：尚未填数，或仅填了一个数（无法判断单调性）
    STATE_INIT = 0
    # 已填数字形成严格递增序列
    STATE_INC = 1
    # 已填数字形成严格递减序列
    STATE_DEC = 2
    # 已填数字不满足严格单调（不再是好数）
    STATE_NOT_GOOD = 3

    def is_digit_sum_good(self, s: int) -> bool:
        """
        判断「数位和」是否为好数
        注：由于输入 r <= 10^15，数位和最大为 15*9 = 135，因此：
        - 若 s < 100：只需十位 != 个位（一位数时十位为0，自然满足）
        - 若 s >= 100：仅可能是 100-135，百位必为1，只需判断 1 < 十位 < 个位
        """
        if s < 100:
            return s // 10 != s % 10
        # 三位数情况：百位固定为1，检查十位和个位是否严格递增
        tens = s // 10 % 10
        units = s % 10
        return 1 < tens < units

    def countFancy(self, l: int, r: int) -> int:
        """统计 [l, r] 区间内的奇妙数数量"""
        
        def calc(val: int) -> int:
            """计算 [0, val] 区间内的奇妙数数量"""
            # 将数字转为数位列表，方便逐位处理
            digits = list(map(int, str(val)))
            n = len(digits)

            @cache
            def dfs(
                i: int,          # 当前处理到第 i 位（从 0 开始）
                digit_sum: int,  # 当前已填数位的和
                prev_digit: int, # 上一位填的数字（仅在已填数时有效）
                state: int,      # 当前状态（STATE_* 常量）
                limit: bool      # 当前位是否受 val 上限限制（True则不能超过 digits[i]）
            ) -> int:
                # ---------------- 递归终止条件 ----------------
                if i == n:
                    # 若当前数是好数（state != NOT_GOOD），或数位和是好数，则计数+1
                    return 1 if (state != self.STATE_NOT_GOOD or self.is_digit_sum_good(digit_sum)) else 0

                res = 0

                # ---------------- 分支1：不填当前位（仅初始状态允许，用于处理位数更少的数） ----------------
                # 仅当 state 为初始且未填过数时，允许跳过当前位（继续前导零）
                can_skip = (state == self.STATE_INIT) and (prev_digit == 0)
                if can_skip:
                    # 跳过当前位：状态保持初始，数位和为0，无前置数字，且不再受上限限制
                    res += dfs(i + 1, 0, 0, self.STATE_INIT, False)

                # ---------------- 分支2：填当前位 ----------------
                # 确定当前位的取值范围 [L, R]
                L = 1 if can_skip else 0  # 若之前跳过了（前导零），则第一位有效数字从1开始
                R = digits[i] if limit else 9  # 若受限制，则不能超过 digits[i]

                for bit in range(L, R + 1):
                    # ---------------- 更新状态 ----------------
                    new_state = state
                    if state == self.STATE_INIT:
                        # 初始状态下，若之前已填过一个数（prev_digit > 0），则判断单调性
                        if prev_digit > 0:
                            if bit > prev_digit:
                                new_state = self.STATE_INC
                            elif bit < prev_digit:
                                new_state = self.STATE_DEC
                            else:
                                new_state = self.STATE_NOT_GOOD  # 相等则不再是好数
                    elif state == self.STATE_INC:
                        # 递增状态下，当前位必须大于前一位，否则变为无效
                        if bit <= prev_digit:
                            new_state = self.STATE_NOT_GOOD
                    elif state == self.STATE_DEC:
                        # 递减状态下，当前位必须小于前一位，否则变为无效
                        if bit >= prev_digit:
                            new_state = self.STATE_NOT_GOOD

                    # ---------------- 更新限制条件 ----------------
                    # 只有之前受限制且当前位取到最大值时，后续位才继续受限制
                    new_limit = limit and (bit == R)

                    # ---------------- 递归到下一位 ----------------
                    res += dfs(
                        i + 1,
                        digit_sum + bit,  # 累加数位和
                        bit,               # 更新前一位数字
                        new_state,         # 更新状态
                        new_limit          # 更新限制
                    )

                return res

            # 初始调用：从第0位开始，数位和为0，无前导数字，初始状态，受上限限制
            return dfs(0, 0, 0, self.STATE_INIT, True)

        # 区间 [l, r] 的奇妙数 = [0, r] 的数量 - [0, l-1] 的数量
        return calc(r) - calc(l - 1)