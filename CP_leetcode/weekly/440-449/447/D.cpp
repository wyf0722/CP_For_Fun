/*************************************************************************
    > File Name: D.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-04-27 14:27
************************************************************************/
#include <algorithm>
#include <bit>
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
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        V<int> ids(n);
        iota(ids.begin(), ids.end(), 0);
        ranges::sort(ids, [&](int i, int j) { return nums[i] < nums[j]; });
        V<int> pos(n);
        for (int i = 0; i < n; i++) {
            pos[ids[i]] = i;
        }

        int mx = bit_width((uint32_t)n);
        V<V<int>> pa(n, V<int>(mx));
        for (int i = 0, j = 0; i < n; i++) {
            while (nums[ids[i]] - nums[ids[j]] > maxDiff) {
                j++;
            }
            pa[i][0] = j;
        }
        // 倍增
        for (int j = 1; j < mx; j++) {
            for (int i = 0; i < n; i++) {
                pa[i][j] = pa[pa[i][j - 1]][j - 1];
            }
        }

        vector<int> ans;
        for (auto &q : queries) {
            int L = pos[q[0]], R = pos[q[1]];
            if (L == R) {
                ans.push_back(0);
                continue;
            }
            if (L > R) {
                swap(L, R);
            }
            int res = 0;
            for (int i = mx - 1; i >= 0; i--) {
                if (pa[R][i] > L) {
                    res |= 1 << i;
                    R = pa[R][i];
                }
            }
            ans.push_back(pa[R][0] > L ? -1 : res + 1);
        }
        return ans;
    }
};