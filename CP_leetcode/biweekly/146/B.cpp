/*************************************************************************
    > File Name: B.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2024-12-22 00:22
************************************************************************/
#include <bits/stdc++.h>
using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#define debug(...) cout << '[' << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

using i64 = long long;
const int MOD = 1e9 + 7;
class Solution {
public:
    int countPathsWithXorValue(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        int dp[m][n][16];
        memset(dp, 0, sizeof(dp));
        dp[0][0][grid[0][0]] = 1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int x = 0; x < 16; x++) {
                    if (i + 1 < m) {
                        dp[i + 1][j][x ^ grid[i + 1][j]] = (dp[i + 1][j][x ^ grid[i + 1][j]] + dp[i][j][x]) % MOD;
                    }
                    if (j + 1 < n) {
                        dp[i][j + 1][x ^ grid[i][j + 1]] = (dp[i][j + 1][x ^ grid[i][j + 1]] + dp[i][j][x]) % MOD;
                    }
                }
            }
        }
        return dp[m - 1][n - 1][k];
    }
};