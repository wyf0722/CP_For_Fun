/*************************************************************************
    > File Name: A.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-01-12 14:00
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
    vector<int> zigzagTraversal(vector<vector<int>>& grid) {
        bool flag = 1, lst = 0;
        vector<int> ans;
        for (auto &row : grid) {
            if (!flag) {
                reverse(row.begin(), row.end());
            }
            flag = !flag;
            for (auto &x : row) {
                if (!lst) {
                    ans.push_back(x);
                }
                lst = !lst;
            }
        }    
        return ans;
    }
};