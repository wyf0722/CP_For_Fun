/*************************************************************************
    > File Name: D.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-02-14 23:10
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
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        // left_bigger[i]: nums[i]是哪些数字左侧最近的更大的数字
        V<V<int>> left_bigger(n);
        // 下一个 >= nums[i] 的位置
        V<int> R(n, n);
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[st.top()] <= nums[i]) {
                R[st.top()] = i;
                st.pop();
            }
            if (!st.empty()) {
                left_bigger[st.top()].push_back(i);
            }
            st.push(i);
        }

        i64 ans = 0;
        // 操作次数
        int cnt = 0;
        // 维护窗口内最大值
        deque<int> q;
        for (int l = 0, r = 0; r < n; r++) {
            while (!q.empty() && nums[q.back()] <= nums[r]) {
                q.pop_back();
            }
            q.push_back(r);

            // nums[r]需要变成窗口内的最大值
            cnt += nums[q.front()] - nums[r];

            // 缩小左端点
            while (cnt > k) {
                int out = nums[l];
                // l会影响以 l 为左侧第一个大于自己的位置
                for (auto & id : left_bigger[l]) {
                    if (id > r) {
                        break;
                    }
                    // 6 3 2 5（移走的是 6）从3 到 3 右侧第一个大于等于自己的位置都要变成 3
                    cnt -= (out - nums[id]) * (min(R[id], r + 1) - id);
                }

                if (!q.empty() && q.front() == l) {
                    q.pop_front();
                }
                l++;
            }

            ans += r - l + 1;
        }
        return ans;
    }
};