/*************************************************************************
    > File Name: A.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2024-11-24 13:06
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
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int ans = -1;
        int n = nums.size();
        for (int x = l; x <= r; x++) {
            int s = 0;
            for (int i = 0; i < n; i++) {
                s += nums[i];
                if (i >= x - 1) {
                    if (s > 0 && (ans == -1 || s < ans)) {
                        ans = s;
                    }
                    s -= nums[i - x + 1];
                }
            }
        }
        return ans;
    }
};