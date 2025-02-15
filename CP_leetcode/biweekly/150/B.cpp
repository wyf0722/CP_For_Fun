/*************************************************************************
    > File Name: B.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-02-16 00:25
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
    double separateSquares(vector<vector<int>>& squares) {
        double lo = 0, hi = 2e9 + 10;
        double all_s = 0;
        for (auto &sq : squares) {
            all_s += 1.0 * sq[2] * sq[2];
        }

        // 在分割线以下的面积
        auto ck = [&](double line) -> bool {
            double s = 0;
            for (auto & sq : squares) {
                int x = sq[0], y = sq[1], l = sq[2];
                if (y >= line) {
                    continue;
                }
                s += (min(1.0 * y + l, line) - y) * l; 
            }
            return s * 2 < all_s;
        };
        while (lo + 1e-6 < hi) {
            double mid = (lo + hi) / 2;
            if (ck(mid)) {
                lo = mid;
            } else {
                hi = mid;
            }
        }      
        return lo;
    }
};