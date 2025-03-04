/*************************************************************************
    > File Name: D.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2024-11-24 00:49
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
    int maxCollectedFruits(vector<vector<int>>& fruits) {
        int n = fruits.size();
        // 最终都要n-1步到达右下角， 左上角小孩只能走对角线
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += fruits[i][i];
            fruits[i][i] = 0;
        }
        auto valid = [&](int x, int y) -> bool {
            return 0 <= x && x < n && 0 <= y && y < n;
        };

        vector<vector<int>> dp(n, vector<int>(n, -1));
        dp[n - 1][0] = fruits[n - 1][0];
        for (int j = 0; j < n; j++) {
            for (int i = n - 1; i >= j; i--) {
                if (dp[i][j] == -1) continue;
                if (valid(i - 1, j + 1) && i - 1 >= j + 1) {
                    chmax(dp[i - 1][j + 1], dp[i][j] + fruits[i - 1][j + 1]);
                }
                if (valid(i, j + 1) && i >= j + 1) {
                    chmax(dp[i][j + 1], dp[i][j] + fruits[i][j + 1]);
                }
                if (valid(i + 1, j + 1) && i + 1 >= j + 1) {
                    chmax(dp[i + 1][j + 1], dp[i][j] + fruits[i + 1][j + 1]);
                }
            }
        }

        dp[0][n - 1] = fruits[0][n - 1];
        for (int i = 0; i < n; i++) {
            for (int j = n - 1; j >= i; j--) {
                if (dp[i][j] == -1) continue;
                if (valid(i + 1, j - 1) && i + 1 <= j - 1) {
                    chmax(dp[i + 1][j - 1], dp[i][j] + fruits[i + 1][j - 1]);
                }
                if (valid(i + 1, j) && i + 1 <= j) {
                    chmax(dp[i + 1][j], dp[i][j] + fruits[i + 1][j]);
                }
                if (valid(i + 1, j + 1) && i + 1 <= j + 1) {
                    chmax(dp[i + 1][j + 1], dp[i][j] + fruits[i + 1][j + 1]);
                }
            }
        }
        return ans + dp[n - 1][n - 2] + dp[n - 2][n - 1];
    }
};