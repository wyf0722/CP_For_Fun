/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-02-02 13:29
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
    int minimumIncrements(vector<int>& nums, vector<int>& target) {
        int n = nums.size(), m = target.size();
        
        // 预处理 target 所有子集的lcm
        V<i64> lcms(1 << m, 1);
        for (int mask = 0; mask < 1 << m; mask++) {
            for (int i = 0; i < m; i++) {
                if (mask >> i & 1) {
                    lcms[mask] = lcm(lcms[mask], target[i]);
                }
            }
        }

        auto op = [&](i64 to, i64 from) -> i64 {
            return (to - from % to) % to;
        };

        V<V<i64>> dp(n + 1, V<i64>(1 << m, inf));
        dp[0][0] = 0;
        for (int i = 0; i < n; i++) {
            dp[i + 1][0] = 0;
            for (int mask = 1; mask < 1 << m; mask++) {
                // 不修改 nums[i]
                dp[i + 1][mask] = min(dp[i + 1][mask], dp[i][mask]);
                // 修改 nums[i]，解决 target 中的部分元素
                // 枚举子集
                for (int sub = mask; sub; sub = (sub - 1) & mask) {
                    dp[i + 1][mask] = min(dp[i + 1][mask], dp[i][mask ^ sub] + op(lcms[sub], nums[i]));
                }
            }
        }
        return dp.back().back();
    }
};