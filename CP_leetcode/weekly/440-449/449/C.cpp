/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-05-11 13:42
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
    long long maxScore(int n, vector<vector<int>>& edges) {
        V<V<int>> g(n);
        V<int> deg(n);
        for (auto& e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
            deg[e[0]]++;
            deg[e[1]]++;
        }
        V<int> vis(n);
        V<V<int>> infos;
        // 环和链
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                // 判断是环还是链
                queue<int> q;
                q.push(i);
                vis[i] = 1;
                bool is_circle = true;
                int nodes = 0;
                while (!q.empty()) {
                    int x = q.front();
                    if (deg[x] != 2) {
                        is_circle = false;
                    }
                    q.pop();
                    nodes++;
                    for (int &y : g[x]) {
                        if (!vis[y]) {
                            vis[y] = 1;
                            q.push(y);
                        }
                    }
                }
                infos.push_back({is_circle ? 1 : 0, nodes});
            }
        }
        i64 ans = 0;
        sort(infos.begin(), infos.end(), [&](auto &e1, auto &e2) {
            if (e1[0] != e2[0]) {
                return e1[0] > e2[0];
            }
            if (e1[0] == 1) {
                return e1[1] < e2[1];
            }
            return e1[1] > e2[1];
        });
        i64 val = n;
        for (auto &info: infos) {
            int flag = info[0], x = info[1];
            deque<i64> q;
            if (x & 1) {
                q.push_back(val--);
                x--;
            } else {
                q.push_back(val--);
                q.push_back(val--);
                x -= 2;
                ans += (val + 1) * (val + 2);
            }
            while (x > 0) {
                i64 d1 = q.front() * val + q.back() * (val - 1);
                i64 d2 = q.front() * (val - 1) + q.back() * val;
                if (d1 > d2) {
                    q.push_front(val--);
                    q.push_back(val--);
                } else {
                    q.push_back(val--);
                    q.push_front(val--);
                }
                x -= 2;
                ans += max(d1, d2);
            }
            if (flag) ans += q.front() * q.back();
        }
        return ans;
    }
};