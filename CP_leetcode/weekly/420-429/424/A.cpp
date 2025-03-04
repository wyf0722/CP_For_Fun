/*************************************************************************
    > File Name: A.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2024-11-17 13:39
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
    int countValidSelections(vector<int>& nums) {
        int sum = 0;
        for (int x : nums) sum += x;
        int cur_sum = 0;
        int ans = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (nums[i] != 0) {
                cur_sum += nums[i];
                continue;
            }
            if (abs(cur_sum - (sum - cur_sum)) == 1) ans++;
            if (cur_sum == sum - cur_sum) {
                ans += 2;
            }
        }
        return ans;
    }
};