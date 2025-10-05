/*************************************************************************
    > File Name: D.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-10-05 13:52
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
    long long maxSumTrionic(vector<int>& nums) {
        int n = nums.size();

        vector<i64> L_inc(n, -infLL), R_inc(n, -infLL);
        for (int i = 0; i < n;) {
            int st = i;
            i++;
            for (; i < n && nums[i - 1] < nums[i]; i++) {}
            if (i - st == 1) continue;
            i64 L_sum = 0, L_mx = -infLL;
            for (int j = st; j < i; j++) {
                L_sum += nums[j];
                if (j >= st + 1) {
                    chmax(L_mx, L_sum);
                }
            }
            L_inc[st] = L_mx;
            i64 R_sum = 0, R_mx = -infLL;
            for (int j = i - 1; j >= st; j--) {
                R_sum += nums[j];
                if (j <= i - 2) {
                    chmax(R_mx, R_sum);
                }
            }
            R_inc[i - 1] = R_mx;
        }
        i64 ans = -infLL;
        for (int i = 0; i < n;) {
            int st = i;
            i++;
            i64 s = nums[st];
            for (; i < n && nums[i - 1] > nums[i]; i++) {
                s += nums[i];
            }
            if (i - st == 1) continue;
            chmax(ans, s + R_inc[st] + L_inc[i - 1] - nums[st] - nums[i - 1]);
        }
        return ans;
    }
};