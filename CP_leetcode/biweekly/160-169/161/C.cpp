/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-09-06 23:05
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
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();
        V<V<pair<int, int>>> g(n);
        for (auto &e : edges) {
            int x = e[0], y = e[1], w = e[2];
            if (!online[x] || !online[y]) continue;
            g[x].emplace_back(y, w);
        }

        auto ck = [&](int lower) -> bool {
            V<i64> dis(n, infLL);
            dis[0] = 0;
            min_heap<pair<i64, int>> h;
            h.emplace(0, 0);
            while (!h.empty()) {
                auto [d, x] = h.top();
                h.pop();
                if (d != dis[x]) {
                    continue;
                }
                for (auto &[y, w] : g[x]) {
                    if (w < lower) continue;
                    if (dis[y] > dis[x] + w) {
                        dis[y] = dis[x] + w;
                        h.emplace(dis[y], y);
                    }
                }
            }
            return dis[n - 1] <= k;
        };

        int lo = -1, hi = inf;
        while (lo + 1 < hi) {
            int mid = lo + (hi - lo) / 2;
            if (ck(mid)) {
                lo = mid;
            } else {
                hi = mid;
            }
        }
        return lo;
    }
};