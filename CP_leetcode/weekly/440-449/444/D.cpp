/*************************************************************************
    > File Name: D.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-04-07 00:31
************************************************************************/
#include <bits/stdc++.h>
#include <vector>

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
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();
        // 相邻元素和，左边数字下标
        set<pair<i64, int>> pairs;
        // 递减的对数
        int bad = 0;
        for (int i = 0; i < n - 1; i++) {
            int x = nums[i], y = nums[i + 1];
            if (x > y) bad++;
            pairs.emplace(x + y, i);
        }
        // 剩余下标
        set<int> ids;
        for (int i = 0; i < n; i++) ids.insert(i);
        
        vector<i64> a(nums.begin(), nums.end());
        int ans = 0;
        while (bad) {
            ans++;

            // 删除相邻元素和最小的
            auto [s, i] = *pairs.begin();
            pairs.erase(pairs.begin());
            
            // 考虑变化pre, i, nxt1, nxt2

            // i, nxt1
            auto it = ids.lower_bound(i);
            auto nxt1_it = next(it);
            int nxt1 = *nxt1_it;
            if (a[i] > a[nxt1]) bad--;

            // pre, i
            if (it != ids.begin()) {
                int pre = *prev(it);
                if (a[pre] > a[i]) bad--;
                if (a[pre] > s) bad++;
                pairs.erase({a[pre] + a[i], pre});
                pairs.emplace(a[pre] + s, pre);
            }

            // nxt1, nxt2
            auto nxt2_it = next(nxt1_it);
            if (nxt2_it != ids.end()) {
                int nxt2 = *nxt2_it;
                if (a[nxt1] > a[nxt2]) bad--;
                if (s > a[nxt2]) bad++;
                pairs.erase({a[nxt1] + a[nxt2], nxt1});
                pairs.emplace(s + a[nxt2], i);
            }

            a[i] = s;
            ids.erase(nxt1_it);
        }
        return ans;
    }
};