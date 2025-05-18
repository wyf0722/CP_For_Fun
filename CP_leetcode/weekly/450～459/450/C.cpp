/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-05-18 13:24
************************************************************************/
#include <bits/stdc++.h>
#include <cctype>

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
    int minMoves(vector<string>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        V<V<pair<int, int>>> pos(26);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if ('A' <= matrix[i][j] && matrix[i][j] <= 'Z') {
                    pos[matrix[i][j] - 'A'].emplace_back(i, j);
                }
            }
        }
        vector<int> vis(26);
        V<V<int>> dp(m, V<int>(n, inf));
        dp[0][0] = 0;
        deque<pair<int, int>> q;
        q.emplace_back(0, 0);
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop_front();
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && matrix[nx][ny] != '#' 
                    && dp[nx][ny] > dp[x][y] + 1) {
                    dp[nx][ny] = dp[x][y] + 1;
                    q.emplace_back(nx, ny);
                }
            }
            if ('A' <= matrix[x][y] && matrix[x][y] <= 'Z' && !vis[matrix[x][y] - 'A']) {
                vis[matrix[x][y] - 'A'] = 1;
                for (auto &[nx, ny] : pos[matrix[x][y] - 'A']) {
                    if (dp[nx][ny] > dp[x][y]) {
                        dp[nx][ny] = dp[x][y];
                        q.emplace_front(nx, ny);
                    }
                }
            }
        }
        return dp[m - 1][n - 1] == inf ? -1 : dp[m - 1][n - 1];
    }
};