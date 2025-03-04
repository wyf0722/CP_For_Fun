/*************************************************************************
    > File Name: A.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2024-12-01 12:42
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
    int getLargestOutlier(vector<int>& nums) {
        int n = nums.size();
        int s = 0;
        unordered_map<int, int> mp;
        for (int x : nums) {
            s += x;
            mp[x]++;
        }
        int ans = -10000000;
        for (int x : nums) {
            int remain = s - x;
            if (remain % 2 == 0) {
                remain /= 2;
                if (x == remain && mp[remain] >= 2) {
                    ans = max(ans, x);
                } else if (x != remain && mp[remain] >= 1) {
                    ans = max(ans, x);
                }
            }
        }
        return ans;
    }
};