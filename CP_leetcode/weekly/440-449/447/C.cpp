/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-04-27 12:43
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
    vector<int> concatenatedDivisibility(vector<int>& nums, int k) {
        ranges::sort(nums);
        int n = nums.size();

        vector<int> digits(n);
        for (int i = 0; i < n; i++) {
            digits[i] = to_string(nums[i]).size();
        }
        vector<int> cnt(1 << n);
        for (int mask = 1; mask < (1 << n); mask++) {
            for (int i = 0; i < n; i++) {
                if (mask >> i & 1) {
                    cnt[mask] += digits[i];
                }
            }
        }

        vector<int> p10{1 % k};
        for (int i = 0; i < n * 10; i++) {
            p10.push_back(p10.back() * 10 % k);
        }

        V<V<int>> dp(k, V<int>(1 << n, n));
        V<V<int>> pre(k, V<int>(1 << n, 0));
        dp[0][0] = -1;
        int total = (1 << n) - 1;
        // 现在已经填的数字二进制表示为 i
        for (int i = 0; i < 1 << n; i++) {
            // 现在已经填的数字的和模 k 为 j
            for (int j = 0; j < k; j++) {
                if (dp[j][i] == n) continue;
                // 剩余可填数字的二进制表示为 remain
                int remain = total ^ i;
                for (; remain; remain -= remain & -remain) {
                    int x = remain & -remain;
                    int d = 31 - __builtin_clz(x);

                    int nj = (j + p10[cnt[i]] * nums[d]) % k;
                    int ni = i | x;

                    if (d < dp[nj][ni]) {
                        dp[nj][ni] = d;
                        pre[nj][ni] = j;
                    }
                }
            }
        }
        if (dp[0][total] == n) return {};
        vector<int> ans;
        int cur = 0;
        int mask = total;
        for (int i = 0; i < n; i++) {
            ans.push_back(nums[dp[cur][mask]]);
            int nxt = pre[cur][mask];
            mask ^= 1 << dp[cur][mask];
            cur = nxt;
        }
        return ans;
    }
};