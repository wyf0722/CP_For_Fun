/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2024-12-22 00:28
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
    bool checkValidCuts(int n, vector<vector<int>>& rectangles) {
        auto ck = [&](vector<vector<int>> &segs) -> bool {
            sort(segs.begin(), segs.end());
            int m = segs.size();
            vector<vector<int>> res;
            res.push_back(segs[0]);
            for (int i = 1; i < m; i++) {
                if (segs[i][0] < res.back()[1]) {
                    res.back()[1] = max(res.back()[1], segs[i][1]);
                } else {
                    res.push_back(segs[i]);
                }
            }
            return res.size() >= 3;
        };

        vector<vector<int>> xs, ys;
        for (auto &r : rectangles) {
            xs.push_back({r[0], r[2]});
            ys.push_back({r[1], r[3]});
        }
        return ck(xs) || ck(ys);
    }
};