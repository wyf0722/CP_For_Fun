/*************************************************************************
    > File Name: A.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2024-12-15 12:38
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
    int buttonWithLongestTime(vector<vector<int>>& events) {
        map<int, int> mp;
        int pre = 0;
        int ans = -1, mx = -1;
        for (int i = 0; i < events.size(); i++) {
            if (mx < events[i][1] - pre || (mx == events[i][1] - pre && ans > events[i][0])) {
                mx = events[i][1] - pre;
                ans = events[i][0];
            }
            pre = events[i][1];
        }
        return ans;
    }
};