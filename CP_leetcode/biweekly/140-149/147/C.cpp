/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-01-05 22:30
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
    int longestSubsequence(vector<int>& nums) {
        int n = nums.size(), mx = ranges::max(nums);
        int mx_d = mx - ranges::min(nums);
        V<V<int>> f(n, V<int>(mx_d + 2));
        V<int> last(mx + 1, -1);

        int ans = 0;
        // f[i][j]以nums[i]结尾且差值至少为j的最长子序列长度
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            for (int j = mx_d; j >= 0; j--) {
                // (i, j) -> (i, j + 1) 倒序遍历
                f[i][j] = max(f[i][j + 1], 1);
                if (x - j >= 0 && last[x - j] >= 0) {
                    chmax(f[i][j], f[last[x - j]][j] + 1);
                }
                if (x + j <= mx && last[x + j] >= 0) {
                    chmax(f[i][j], f[last[x + j]][j] + 1);
                }
                chmax(ans, f[i][j]);
            }
            last[x] = i;
        }
        return ans;
    }
};