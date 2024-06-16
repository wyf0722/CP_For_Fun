"""
埃氏筛
"""
MX = 10**5 + 10
prime = []
is_prime = [True] * (MX + 1)
is_prime[0] = is_prime[1] = False
for i in range(2, MX + 1):
    if is_prime[i]:
        prime.append(i)
        for j in range(i * i, MX + 1, i):
            is_prime[j] = False

'''
组合数
'''
MOD = 998244353
N = 1000
fac = [1]
for i in range(1, N + 1):
    fac.append(fac[-1] * i % MOD)
fac_inv = [1] * (N + 1)
fac_inv[N] = pow(fac[N], MOD - 2, MOD)
for i in range(N - 1, 0, -1):
    fac_inv[i] = fac_inv[i + 1] * (i + 1) % MOD
def Comb(n:int, m:int) -> int:
    assert n >= m and n >= 0 and m >= 0
    return fac[n] * fac_inv[m] % MOD * fac_inv[n - m] % MOD