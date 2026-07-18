/*************************************************************************
    > File Name: A.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2026-07-19 01:07
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
    int maxDigitRange(vector<int>& nums) {
        vector<int> d;
        for (int x : nums) {
            int mx = -1, mn = 10;
            for (int temp = x; temp; temp /= 10) {
                mx = max(mx, temp % 10);
                mn = min(mn, temp % 10);
            }
            d.push_back(mx - mn);
        }
        int t = ranges::max(d);
        int ans = 0;
        for (int i = 0; i < d.size(); i++) {
            if (d[i] == t) {
                ans += nums[i];
            }
        }
        return ans;
    }
};