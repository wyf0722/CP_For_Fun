/*************************************************************************
    > File Name: D_Even_String.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-05-28 19:17
************************************************************************/
#include <bits/stdc++.h>

using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#define debug(...) cout << '[' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

using i64 = long long;
const int inf = INT_MAX / 2 - 100;
const i64 infLL = LLONG_MAX / 3;
constexpr int MOD = 998244353; // 998244353 1000000007
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

#define MULTICASE 1
V<i64> fac;
int init = []() {
    fac.push_back(1);
    for (int i = 1; i <= 5e5 + 5; i++) {
        fac.push_back(fac.back() * i % MOD);
    }
    return 0;
}();

i64 power(i64 x, i64 n) {
    i64 ans = 1;
    for (; n; n /= 2) {
        if (n & 1) {
            ans = ans * x % MOD;
        }
        x = x * x % MOD;
    }
    return ans;
}

void solve() {
    V<int> c(26);
    int n = 0;
    i64 ans = 1;
    for (int i = 0; i < 26; i++) {
        cin >> c[i];
        n += c[i];
        ans = ans * fac[c[i]] % MOD;
    }
    int m = n / 2;
    ans = power(ans, MOD - 2) * fac[m] % MOD * fac[n - m] % MOD;
    V<int> dp(m + 1);
    dp[0] = 1;
    for (int x : c) {
        if (x == 0) continue;
        for (int i = m; i >= x; i--) {
            dp[i] += dp[i - x];
            dp[i] %= MOD;
        }
    }
    cout << ans * dp[m] % MOD << endl;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(20);
    int T = 1;
#if MULTICASE
    cin >> T;
#endif
    while (T--) {
        solve();
    }
    return 0;
}