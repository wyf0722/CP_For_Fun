/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-05-04 13:46
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

class Solution {
public:
    int minTravelTime(int l, int n, int k, vector<int>& position, vector<int>& time) {
        vector<int> s(n + 1);
        for (int i = 1; i <= n; i++) {
            s[i] = s[i - 1] + time[i - 1];
        }
        // dp[left_k][pos][pre] 剩余 left_k 次合并操作，当前在 pos，上一个合并位置是 pre
        V<V<V<int>>> dp(k + 1, V<V<int>>(n, V<int>(n, inf)));
        for (int pre = 0; pre < n; pre++) {
            dp[0][n - 1][pre] = 0;
        }
        for (int left_k = 0; left_k <= k; left_k++) {
            for (int i = n - 2; i >= 0; i--) {
                for (int pre = 0; pre <= i; pre++) {
                    int r = inf;
                    int t = s[i + 1] - s[pre];
                    // [pre, nxt] 删除 [i + 1, nxt - 1]
                    // nxt - 1 - i <= left_k
                    // nxt <= left_k + i + 1
                    for (int nxt = i + 1; nxt < min(n, i + 2 + left_k); nxt++) {
                        chmin(r, dp[left_k - (nxt - 1 - i)][nxt][i + 1] + t * (position[nxt] - position[i]));
                    }
                    dp[left_k][i][pre] = r;
                }
            }
        }
        return dp[k][0][0];
    }
};