/*************************************************************************
    > File Name: D.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-05-25 00:35
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

class Solution {
public:
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size() + 1;
        vector<int> P{1};
        for (int i = 1; i <= n; i++) {
            P.push_back(P.back() * 2 % MOD);
        }
        V<V<int>> g(n);
        for (auto &e : edges) {
            int x = e[0], y = e[1];
            x--, y--;
            g[x].push_back(y);
            g[y].push_back(x);
        }
        V<V<int>> pa(n, V<int>(20, -1));
        V<int> d(n, 0);
        auto f = [&](auto &&self, int x, int fa, int dep) -> void {
            d[x] = dep;
            pa[x][0] = fa;
            for (int i = 1; i < 20; i++) {
                if (pa[x][i - 1] != -1) {
                    pa[x][i] = pa[pa[x][i - 1]][i - 1];
                }
            }
            for (int y : g[x]) {
                if (y != fa) {
                    self(self, y, x, dep + 1);
                }
            }
        };
        f(f, 0, -1, 0);
        auto lca = [&](int x, int y) -> int {
            if (d[x] < d[y]) {
                swap(x, y);
            }
            // 跳到同一层
            for (int delta = d[x] - d[y]; delta; delta -= delta & -delta) {
                int bit = __builtin_ctz(delta);
                x = pa[x][bit];
            }
            if (x == y) {
                return x;
            }
            for  (int i = 19; i >= 0; i--) {
                if (pa[x][i] != pa[y][i]) {
                    x = pa[x][i];
                    y = pa[y][i];
                }
            }
            return pa[x][0];
        };
        V<int> ans;
        for (auto &q : queries) {
            int x = q[0], y = q[1];
            x--, y--;
            int z = lca(x, y);
            int len = d[x] + d[y] - 2 * d[z];
            if (len == 0) ans.push_back(0);
            else ans.push_back(P[len - 1]);
        }
        return ans;
    }
};