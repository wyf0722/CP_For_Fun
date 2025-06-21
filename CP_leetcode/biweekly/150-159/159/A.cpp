/*************************************************************************
    > File Name: A.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-06-22 00:16
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
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<int> even, odd;
        for (int i = 0; i < n; i++) {
            if (nums[i] % 2 == 0) even.push_back(i);
            else odd.push_back(i);
        }
        int ans = -1;
        if (even.size() == (n + 1) / 2) {
            int even_op = 0;
            for (int i = 0, j = 0; i < n; i += 2, j++) {
                even_op += abs(even[j] - i);
            }
            if (ans == -1 || ans > even_op) {
                ans = even_op;
            }
        }
        if (odd.size() == (n + 1) / 2) {
            int odd_op = 0;
            for (int i = 0, j = 0; i < n; i += 2, j++) {
                odd_op += abs(odd[j] - i);
            }
            if (ans == -1 || ans > odd_op) {
                ans = odd_op;
            }
        }
        return ans;
    }
};