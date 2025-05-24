/*************************************************************************
    > File Name: B.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-05-25 00:17
************************************************************************/
#include <bits/stdc++.h>
using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#define debug(...) cout << '[' << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

using i64 = long long;
class Solution {
public:
    int maxSubstrings(string word) {
        int n = word.size();
        vector<int> pos(26, n), nxt(n, n);
        for (int i = n - 1; i >= 0; i--) {
            int ch = word[i] - 'a';
            nxt[i] = pos[ch];
            pos[ch] = i;
        }
        vector<int> dp(n + 1, 0);
        for (int i = 0; i < n; i++) {
            if (i) dp[i] = max(dp[i], dp[i - 1]);
            int ni = nxt[i];
            for (; ni < n && ni - i + 1 < 4; ni = nxt[ni]) {}
            if (ni < n) {
                dp[ni + 1] = max(dp[ni + 1], dp[i] + 1);
            }
        }
        return ranges::max(dp);
    }
};