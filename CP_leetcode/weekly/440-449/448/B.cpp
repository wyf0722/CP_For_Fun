/*************************************************************************
    > File Name: B.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-05-04 13:28
************************************************************************/
#include <bits/stdc++.h>
#include <vector>
using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#define debug(...) cout << '[' << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

using i64 = long long;
class Solution {
public:
    vector<vector<int>> specialGrid(int N) {
        int len = 1 << N;
        vector<vector<int>> ans(len, vector<int>(len, 0));
        int idx = len * len - 1;
        
        auto f = [&](auto &self, int i, int j, int d) -> void {
            if (d <= 1) {
                ans[i][j] = idx--;
                return;
            }
            self(self, i, j, d / 2);
            self(self, i + d / 2, j, d / 2);
            self(self, i + d / 2, j + d / 2, d / 2);
            self(self, i, j + d / 2, d / 2);
        };
        f(f, 0, 0, len);
        return ans;
    }
};