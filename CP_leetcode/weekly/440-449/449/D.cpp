/*************************************************************************
    > File Name: D.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-05-11 15:36
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

V<V<int>> rotate(const V<V<int>> &a) {
    int m = a.size(), n = a[0].size();
    V<V<int>> b(n, V<int>(m));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            b[j][m - i - 1] = a[i][j];
        }
    }
    return b;
}

class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        i64 total = 0;
        for (auto &row : grid) {
            for (int &x : row) {
                total += x;
            }
        }

        // s - x == total - s -> 2 * s - total == x
        auto calc = [&](V<V<int>> a) -> bool {
            int m = a.size(), n = a[0].size();

            auto f = [&]() -> bool {
                unordered_set<i64> st{0};
                i64 s = 0;
                for (int i = 0; i < m - 1; i++) {
                    auto &row = a[i];
                    for (int j = 0; j < n; j++) {
                        int x = row[j];
                        s += x;
                        // 第一行不能删除中间元素
                        if (i == 0 && 0 < j && j < n - 1) {
                            continue;
                        }
                        st.insert(x);
                    }

                    // 只有一列
                    if (n == 1) {
                        if (s * 2 == total || s * 2 - total == a[0][0] || s * 2 - total == a[i][0]) {
                            return true;
                        }
                        continue;
                    }

                    if (st.contains(s * 2 - total)) {
                        return true;
                    }
                    
                    // 进入第二行后可以删除第一行所有元素
                    if (i == 0) {
                        for (int j = 0; j < n; j++) {
                            st.insert(a[i][j]);
                        }
                    }
                }
                return false;
            };
            // 上半部分删除元素
            if (f()) return true;
            // 下半部分删除元素
            reverse(a.begin(), a.end());
            return f();
        };

        // 水平 or 垂直
        return calc(grid) || calc(rotate(grid));
    }
};