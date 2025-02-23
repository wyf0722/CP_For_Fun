/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-02-24 00:11
************************************************************************/
#include <bits/stdc++.h>
using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#define debug(...) cout << '[' << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

const int MOD = 10;
const int MX = 1e5;
vector<int> f(MX + 1), inv_f(MX + 1), p2(MX + 1), p5(MX + 1);

int power(int x, int n) {
    int res = 1;
    for (; n; n >>= 1, x = x * x % MOD) {
        if (n & 1) {
            res = res * x % MOD;
        }
    }
    return res;
}

auto init = []() -> int {
    f[0] = 1;
    for (int i = 1; i <= MX; i++) {
        int x = i;
        // 计算 2 和 5 的幂次
        int e2 = 0, e5 = 0;
        while (x % 2 == 0) {
            e2++;
            x /= 2;
        }
        while (x % 5 == 0) {
            e5++;
            x /= 5;
        }
        f[i] = f[i - 1] * x % MOD; // ⚠️
        p2[i] = p2[i - 1] + e2;
        p5[i] = p5[i - 1] + e5;
    }

    // 欧拉定理 逆元
    inv_f[MX] = power(f[MX], 3);
    for (int i = MX; i > 0; i--) {
        // 去掉因子 2 和 5
        int x = i;
        while (x % 2 == 0) x /= 2;
        while (x % 5 == 0) x /= 5;
        inv_f[i - 1] = inv_f[i] * x % MOD; // ⚠️
    }
    return 0;
}();

int comb(int n, int k) {
    // n! / (k! (n - k)!)
    // 上下同时提取出因子 2 和 5
    return f[n] * inv_f[k] * inv_f[n - k] * 
    power(2, p2[n] - p2[k] - p2[n - k]) * 
    power(5, p5[n] - p5[k] - p5[n - k]) % MOD;
}

// [0, n - 2] and [1, n - 1]
// sum(C(m - 1, i) * a[i] for i in range(m))
class Solution {
public:
    bool hasSameDigits(string s) {
        int x = 0, y = 0;
        int n = s.size();
        for (int i = 0; i < n - 1; i++) {
            x += comb(n - 2, i) * (s[i] - '0');
            y += comb(n - 2, i) * (s[i + 1] - '0');
            x %= MOD;
            y %= MOD;
        }
        return x == y;
    }
};