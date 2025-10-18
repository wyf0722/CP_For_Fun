/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-10-12 23:31
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
    int longestBalanced(string s) {
        int n = s.size();
        int ans = 0;

        // 1 char
        for (int i = 0; i < n;) {
            int st = i;
            for (; i < n && s[i] == s[st];i++) {}
            chmax(ans, i - st);
        }

        // 2 char
        // s_a[j] - s_a[i] == s_b[j] - s_b[i]
        auto f = [&](char x, char y) -> void {
            for (int i = 0; i < n; i++) {
                unordered_map<int, int> first_occur = {{0, i - 1}};
                int diff = 0;
                for (; i < n && (s[i] == x || s[i] == y); i++) {
                    diff += (s[i] == x ? 1 : -1);
                    if (first_occur.contains(diff)) {
                        chmax(ans, i - first_occur[diff]);
                    } else {
                        first_occur[diff] = i;
                    }
                }
            }
        };
        f('a', 'b');
        f('a', 'c');
        f('b', 'c');

        // 3 char
        unordered_map<long long, int> first_occur = {{1LL * n << 32 | n, -1}};
        vector<int> cnt(3);
        for (int i = 0; i < n; i++) {
            cnt[s[i] - 'a']++;
            long long p = 1LL * (cnt[0] - cnt[1] + n) << 32 | (cnt[1] - cnt[2] + n);
            if (first_occur.contains(p)) {
                ans = max(ans, i - first_occur[p]);
            } else {
                first_occur[p] = i;
            }
        }
        return ans;
    }
};