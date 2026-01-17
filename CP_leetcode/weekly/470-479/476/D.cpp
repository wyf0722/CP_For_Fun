/*************************************************************************
    > File Name: D.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2026-01-17 19:06
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
    vector<long long> countStableSubarrays(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> segs;
        vector<i64> s = {0};
        for (int i = 0; i < n;) {
            int st = i;
            i++;
            for (; i < n && nums[i] >= nums[i - 1]; i++) {}
            segs.push_back(st);
            int d = i - st;
            s.push_back(s.back() + 1LL * d * (d + 1) / 2);
        }

        vector<i64> ans;

        for (auto &q : queries) {
            int l = q[0], r = q[1];
            // > l 的第一个区间
            int i = upper_bound(segs.begin(), segs.end(), l) - segs.begin();
            // 含有 r 的最后一个区间
            int j = upper_bound(segs.begin(), segs.end(), r) - segs.begin() - 1;

            if (i > j) {
                int d = r - l + 1;
                ans.push_back(1LL * d * (d + 1) / 2);
                continue;
            }

            int d1 = segs[i] - l;
            int d2 = r -  segs[j] + 1;
            // [i, j - 1]
            ans.push_back(1LL * d1 * (d1 + 1) / 2 + 1LL * d2 * (d2 + 1) / 2 + s[j] - s[i]);
        }

        return ans;
    }
};