/*************************************************************************
    > File Name: B.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-06-30 16:20
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
    vector<int> longestCommonPrefix(vector<string>& words) {
        int n = words.size();
        auto f = [&](string w1, string w2) -> int {
            for (int i = 0; i < min(w1.size(), w2.size()); i++) {
                if (w1[i] != w2[i]) return i;
            }
            return min(w1.size(), w2.size());
        };
        vector<int> left1(n);
        for (int i = 1; i < n; i++) {
            left1[i] = f(words[i - 1], words[i]);
        }
        vector<int> left2(n);
        for (int i = 2; i < n; i++) {
            left2[i] = f(words[i - 2], words[i]);
        }
        vector<int> suf_left1(n + 1);
        for (int i = n - 1; i >= 0; i--) {
            suf_left1[i] = max(left1[i], suf_left1[i + 1]);
        }
        vector<int> pre_left1(n);
        for (int i = 1; i < n; i++) {
            pre_left1[i] = max(left1[i], pre_left1[i - 1]);
        }
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            int pre = i ? pre_left1[i - 1] : 0;
            int suf = i + 2 < n ? suf_left1[i + 2] : 0;
            int l2 = i + 1 < n ? left2[i + 1] : 0;
            ans[i] = max({pre, suf, l2});
        }
        return ans;
    }
};