/*************************************************************************
    > File Name: D.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-05-12 00:26
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

vector<vector<int>> dirs{{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                         {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
class Solution {
public:
    int maxMoves(int kx, int ky, vector<vector<int>>& positions) {
        int n = positions.size();
        int dis[n][50][50];
        memset(dis, -1, sizeof(dis));
        // 马到兵 -> 兵到其他格子
        for (int i = 0; i < n; i++) {
            int st_x = positions[i][0], st_y = positions[i][1];
            dis[i][st_x][st_y] = 0;
            queue<pair<int, int>> q;
            q.emplace(st_x, st_y);
            while (!q.empty()) {
                int sz = q.size();
                while (sz--) {
                    auto [x, y] = q.front();
                    q.pop();
                    for (int d = 0; d < 8; d++) {
                        int nx = x + dirs[d][0], ny = y + dirs[d][1];
                        if (0 <= nx && nx < 50 && 0 <= ny && ny < 50 && dis[i][nx][ny] == -1) {
                            dis[i][nx][ny] = dis[i][x][y] + 1;
                            q.emplace(nx, ny);
                        }
                    }
                }
            }
        }

        positions.push_back({kx, ky});
        V<V<int>> mem(n + 1, V<int>(1 << n, -1));
        int u = (1 << n) - 1;
        auto f = [&](auto &&self, int i, int mask) -> int {
            if (mask == 0) return 0;
            int x = positions[i][0], y = positions[i][1];
            int &r = mem[i][mask];
            if (r != -1) return r;
            int used = mask ^ u;
            if (__builtin_popcount(used) % 2 == 0) {
                // Alice
                for (int j = 0; j < n; j++) {
                    if (mask >> j & 1) {
                        chmax(r, self(self, j, mask ^ (1 << j)) + dis[j][x][y]);
                    }
                }
            } else {
                // Bob
                r = inf;
                for (int j = 0; j < n; j++) {
                    if (mask >> j & 1) {
                        chmin(r, self(self, j, mask ^ (1 << j)) + dis[j][x][y]);
                    }
                }
            }
            return r;
        };
        return f(f, n, u);
    }
};