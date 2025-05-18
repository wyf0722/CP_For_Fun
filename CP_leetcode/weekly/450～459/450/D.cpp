/*************************************************************************
    > File Name: D.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-05-18 13:43
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
    vector<int> minimumWeight(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size() + 1;
        int mx_d = 17;
        V<V<int>> pa(n, V<int>(mx_d, -1));
        V<int> dis(n), dep(n);
        V<V<pair<int, int>>> g(n);
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }
        auto dfs = [&](auto &&self, int x, int fa) -> void {
            pa[x][0] = fa;
            for (int i = 1; i < mx_d; i++) {
                if (pa[x][i - 1] != -1) {
                    pa[x][i] = pa[pa[x][i - 1]][i - 1];
                }
            }
            for (auto &[y, w] : g[x]) {
                if (y == fa) continue;
                dep[y] = dep[x] + 1;
                dis[y] = dis[x] + w;
                self(self, y, x);
            }
        };
        dfs(dfs, 0, -1);

        // 跳到同一层
        auto jump = [&](int x, int y) -> int {
            if (dep[x] > dep[y]) {
                swap(x, y);
            }
            int d = dep[y] - dep[x];
            for (int i = mx_d - 1; i >= 0; i--) {
                if (d >> i & 1) {
                    y = pa[y][i];
                }
            }
            return y;
        };
        // lca
        auto LCA = [&](int x, int y) -> int {
            if (dep[x] > dep[y]) {
                swap(x, y);
            }
            y = jump(x, y);
            if (x == y) {
                return x;
            }
            for (int i = mx_d - 1; i >= 0; i--) {
                if (pa[x][i] != pa[y][i]) {
                    x = pa[x][i];
                    y = pa[y][i];
                }
            }
            return pa[x][0];
        };
        auto get_d = [&](int x, int y) {
            int lca = LCA(x, y);
            return dis[x] + dis[y] - 2 * dis[lca];
        };

        vector<int> ans;
        for (auto &q : queries) {
            int x = q[0], y = q[1], z = q[2];
            int d1 = get_d(x, y), d2 = get_d(x, z), d3 = get_d(y, z);
            int r = (d1 + d2 + d3) / 2;
            ans.push_back(r);
        }
        return ans;
    }
};