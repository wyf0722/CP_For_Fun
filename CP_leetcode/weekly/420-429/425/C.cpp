/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2024-11-24 13:21
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
    int minArraySum(vector<int>& nums, int k, int op1, int op2) {
        int n = nums.size();
        vector<vector<vector<int>>> mem(n, vector<vector<int>>(op1 + 1, vector<int>(op2 + 1, -1)));
        auto f = [&](auto &&self, int i, int c1, int c2) -> int {
            if (i < 0) {
                return 0;
            }
            if (mem[i][c1][c2] != -1) return mem[i][c1][c2];
            // op1
            int r = 0;
            if (c1) {
                r = max(r, self(self, i - 1, c1 - 1, c2) + nums[i] / 2);
            }
            // op2
            if (c2 && nums[i] >= k) {
                r = max(r, self(self, i - 1, c1, c2 - 1) + k);
            }
            // op1 op2
            if (c1 && c2 && (nums[i] + 1) / 2 >= k) {
                r = max(r, self(self, i - 1, c1 - 1, c2 - 1) + nums[i] / 2 + k);
            }
            // op2 op1
            if (c1 && c2 && nums[i] >= k) {
                r = max(r, self(self, i - 1, c1 - 1, c2 - 1) + k + (nums[i] - k) / 2);
            }
            // no op
            r = max(r, self(self, i - 1, c1, c2));
            mem[i][c1][c2] = r;
            return r;
        };
        int s = 0;
        for (int x : nums) s += x;
        return s - f(f, n - 1, op1, op2);
    }
};