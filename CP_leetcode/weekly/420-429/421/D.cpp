/*************************************************************************
    > File Name: D.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-04-11 00:29
************************************************************************/
#include <bits/stdc++.h>
#include <vector>

using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#define debug(...) cout << '[' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

using i64 = long long;
const int inf = INT_MAX / 2 - 100;
const i64 infLL = LLONG_MAX / 3;
constexpr int MOD = 1000000007; // 998244353 1000000007
int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};
template <class T> using V = vector<T>;
template<typename T> using min_heap=priority_queue<T,vector<T>,greater<T>>;
template<typename T> using max_heap=priority_queue<T>;

constexpr int popcount(int x) { return __builtin_popcount(x); }
constexpr int topbit(int x) { return x == 0 ? 0 : 31 - __builtin_clz(x); }

template <class T> bool chmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }  // set a = min(a,b)
template <class T> bool chmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }  // set a = max(a,b)

template<class T, class U> T fstTrue(T lo, T hi, U f) { ++hi; assert(lo <= hi); while (lo < hi) { T mid = lo + (hi - lo) / 2; f(mid) ? hi = mid : lo = mid + 1; } return lo; }
template<class T, class U> T lstTrue(T lo, T hi, U f) { --lo; assert(lo <= hi); while (lo < hi) { T mid = lo + (hi - lo + 1) / 2; f(mid) ? lo = mid : hi = mid - 1; } return lo; }

constexpr int SIZE = 26;
using Matrix = array<array<int, SIZE>, SIZE>;
// 返回矩阵 a 和矩阵 b 相乘的结果
Matrix mul(Matrix& a, Matrix& b) {
    Matrix c{};
    for (int i = 0; i < SIZE; i++) {
        for (int k = 0; k < SIZE; k++) {
            if (a[i][k] == 0) {
                continue;
            }
            for (int j = 0; j < SIZE; j++) {
                c[i][j] = (c[i][j] + (long long) a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return c;
}

// 返回 n 个矩阵 a 相乘的结果
Matrix pow(Matrix a, int n) {
    Matrix res = {};
    for (int i = 0; i < SIZE; i++) {
        res[i][i] = 1; // 单位矩阵
    }
    while (n) {
        if (n & 1) {
            res = mul(res, a);
        }
        a = mul(a, a);
        n >>= 1;
    }
    return res;
}

class Solution {
public:
    int lengthAfterTransformations(string s, int t, vector<int>& nums) {
        Matrix m{};
        for (int i = 0; i < SIZE; i++) {
            for (int j = 1; j <= nums[i]; j++) {
                m[i][(i + j) % SIZE] = 1;
            }
        }
        m = pow(m, t);
        int cnt[SIZE]{};
        for (char c : s) {
            cnt[c - 'a']++;
        }
        i64 ans = 0;
        for (int i = 0; i < SIZE; i++) {
            i64 row_sum = 0;
            for (int j = 0; j < SIZE; j++) {
                row_sum += m[i][j];
            }
            ans += row_sum * cnt[i];
            ans %= MOD;
        }
        return ans % MOD;;
    }
};