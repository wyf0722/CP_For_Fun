/*************************************************************************
    > File Name: D.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-06-20 20:23
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
    vector<int> findMedian(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        V<i64> dis(n);
        V<V<int>> pa(n, V<int>(22, -1));  
        V<int> depth(n);
        V<V<pair<int, int>>> g(n);
        for (auto &edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }   

        auto work = [&](auto &&self, int x, int fa) -> void {
            pa[x][0] = fa;
            for (int i = 1; i < 22; i++) {
                if (pa[x][i - 1] == -1) break;
                pa[x][i] = pa[pa[x][i - 1]][i - 1];
            }
            for (auto &[y, w] : g[x]) {
                if (y == fa) continue;
                depth[y] = depth[x] + 1;
                dis[y] = dis[x] + w;
                self(self, y, x);
            }
        };
        work(work, 0, -1);

        auto get_lca = [&](int x, int y) -> int {
            if (depth[x] > depth[y]) {
                swap(x, y);
            }
            // 跳到同一层
            int delta = depth[y] - depth[x];
            for (int i = 0; i < 22; i++) {
                if (delta >> i & 1) {
                    y = pa[y][i];
                }
            }
            if (x == y) {
                return x;
            }
            for (int i = 21; i >= 0; i--) {
                if (pa[x][i] != pa[y][i]) {
                    x = pa[x][i];
                    y = pa[y][i];
                }
            }
            return pa[x][0];
        };

        // 跳跃距离 <= d
        auto jump = [&](int x, i64 d) -> int {
            i64 dx = dis[x];
            for (int i = 21; i >= 0; i--) {
                int p = pa[x][i];
                if (p != - 1 && dx - dis[p] <= d) {
                    x = p;
                }
            }
            return x;
        };

        vector<int> ans;
        for (auto &query : queries) {
            int x = query[0], y = query[1];
            if (x == y) {
                ans.push_back(x);
                continue;
            }
            int lca = get_lca(x, y);
            i64 dis_xy = dis[x] + dis[y] - 2 * dis[lca];
            i64 half = (dis_xy + 1) / 2;
            int res;
            if (dis[x] - dis[lca] >= half) {
                // x->lca
                int r = jump(x, half - 1);
                // 再往上跳一步才能超过
                ans.push_back(pa[r][0]);
            } else {
                // y->lca
                int r = jump(y, dis_xy - half);
                ans.push_back(r);
            }
        }
        return ans;
    }
};