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

