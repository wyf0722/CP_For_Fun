/*************************************************************************
    > File Name: A.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-02-09 13:28
************************************************************************/
#include <bits/stdc++.h>
using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#define debug(...) cout << '[' << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

class Solution {
public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        for (int i = 0; i < n; i++) {
            vector<int> nums;
            for (int x = i, y = 0; x < n && y < n; x++, y++) {
                nums.push_back(grid[x][y]);
            }
            ranges::sort(nums, greater<int>());
            for (int x = i, y = 0, id = 0; x < n && y < n; x++, y++, id++) {
                grid[x][y] = nums[id];
            }
        }
        for (int i = n - 2; i >= 0; i--) {
            vector<int> nums;
            for (int x = i, y = n - 1; x >= 0 && y >= 0; x--, y--) {
                nums.push_back(grid[x][y]);
            }
            ranges::sort(nums, greater<int>());
            for (int x = i, y = n - 1, id = 0; x >= 0 && y >= 0; x--, y--, id++) {
                grid[x][y] = nums[id];
            }
        }
        return grid;
    }
};