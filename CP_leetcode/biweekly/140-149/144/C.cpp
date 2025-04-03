/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-04-03 21:02
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
    int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
        ranges::sort(queries, [](auto &e1, auto &e2) { return e1[0] < e2[0]; });
        int n = nums.size(), j = 0, sum_d = 0;
        vector<int> dif(n + 1);
        priority_queue<int> pq;
        for (int i = 0; i < n; i++) {
            sum_d += dif[i];
            while (j < queries.size() && queries[j][0] <= i) {
                pq.push(queries[j][1]);
                j++;
            }
            while (sum_d < nums[i] && !pq.empty() && pq.top() >= i) {
                sum_d++;
                dif[pq.top() + 1]--;
                pq.pop();
            }
            if (sum_d < nums[i]) return -1;
        }
        return pq.size();
    }
};