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
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        int lo = -2, hi = queries.size();

        auto ck = [&](int x) -> bool {
            vector<int> d(n + 1);
            for (int i = 0; i <= x; i++) {
                d[queries[i][0]] += queries[i][2];
                d[queries[i][1] + 1] -= queries[i][2];
            }
            for (int i = 1; i <= n; i++) {
                d[i] += d[i - 1];
            }
            for (int i = 0; i < n; i++) {
                if (nums[i] > d[i]) return false;
            }
            return true;
        };

        while (lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if (ck(mid)) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        return hi == queries.size() ? -1 : hi + 1;
    }
};