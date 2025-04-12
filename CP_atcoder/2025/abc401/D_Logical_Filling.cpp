/*************************************************************************
    > File Name: D_Logical_Filling.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-04-12 23:26
************************************************************************/
#include <bits/stdc++.h>
#include <iostream>

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

#define MULTICASE 0
void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    // 先满足o 不相邻
    for (int i = 0; i < n; i++) {
        if (s[i] == 'o') {
            if (i) s[i - 1] = '.';
            if (i + 1 < n) s[i + 1] = '.';
        }
    }
    int mx = count(s.begin(), s.end(), 'o');

    // o 已经全部出现
    if (k == mx) {
        for (auto &c : s) if (c == '?') c = '.';
        cout << s << '\n';
        return;
    }

    for (int i = 0; i < n;) {
        if (s[i] == '?') {
            int st = i;
            while (i < n && s[i] == '?') i++;
            mx += (i - st + 1) / 2;
        } else {
            i++;
        }
    }

    if (k == mx) {
        for (int i = 0; i < n;) {
            if (s[i] == '?') {
                int st = i;
                while (i < n && s[i] == '?') i++;
                // 只有区间长度为奇数，才能确定
                if ((i - st) & 1) {
                    for (int d = 0; d < i - st; d++) {
                        s[st + d] = "o."[d % 2];
                    }
                }
            } else {
                i++;
            }
        }
    }

    cout << s << '\n';
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