/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-04-27 00:18
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
// j(n) = pi[j(n-1) - 1]
vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

// 在text中查找pattern的出现位置
vector<int> find_occurrences(string text, string pattern) {
    string cur = pattern + '#' + text;
    int sz1 = text.size(), sz2 = pattern.size();
    vector<int> v;
    vector<int> lps = prefix_function(cur);
    for (int i = sz2 + 1; i <= sz1 + sz2; i++) {
        if (lps[i] == sz2)
            v.push_back(i - 2 * sz2);
    }
    return v;
}
class Solution {
public:
    int countCells(vector<vector<char>>& grid, string pattern) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> ck(m, vector<int>(n, 0));
        // 水平子串
        string hs = "";
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) hs.push_back(grid[i][j]);
        auto h_idx = find_occurrences(hs, pattern);
        vector<int> hd(n * m + 1, 0);
        for (auto &idx : h_idx) {
            hd[idx]++;
            hd[idx + pattern.size()]--;
        }
        for (int i = 0; i < n * m; i++) {
            if (i) hd[i] += hd[i - 1];
            int x = i / n, y = i % n;
            if (hd[i]) ck[x][y] += 1;
        }
        
        // 垂直子串
        string vs = "";
        for (int j = 0; j < n; j++) for (int i = 0; i < m; i++) vs.push_back(grid[i][j]);
        auto y_idx = find_occurrences(vs, pattern);
        vector<int> vd(n * m + 1, 0);
        for (auto &idx : y_idx) {
            vd[idx]++;
            vd[idx + pattern.size()]--;
        }
        for (int i = 0; i < n * m; i++) {
            if (i) vd[i] += vd[i - 1];
            int x = i % m, y = i / m;
            if (vd[i]) ck[x][y] += 1;
        }
        int ans = 0;
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) ans += ck[i][j] == 2;
        return ans;
    }
};