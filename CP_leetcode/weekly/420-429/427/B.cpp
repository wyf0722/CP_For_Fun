/*************************************************************************
    > File Name: B.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2024-12-08 13:43
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
    int maxRectangleArea(vector<vector<int>>& points) {
        int ans = -1;
        int n = points.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    for (int l = k + 1; l < n; l++) {
                        vector<vector<int>> choose;
                        choose.push_back(points[i]);
                        choose.push_back(points[j]);
                        choose.push_back(points[k]);
                        choose.push_back(points[l]);
                        sort(choose.begin(), choose.end());
                        if (choose[0][0] != choose[1][0]) continue;
                        if (choose[2][0] != choose[3][0]) continue;
                        if (choose[0][1] != choose[2][1]) continue;
                        if (choose[1][1] != choose[3][1]) continue;
                        int x1 = choose[0][0], x2 = choose[2][0];
                        int y1 = choose[0][1], y2 = choose[1][1];
                        bool ok = true;
                        for (int m = 0; m < n; m++) {
                            if (m != i && m != j && m != k && m != l && x1 <= points[m][0] && points[m][0] <= x2 && y1 <= points[m][1] && points[m][1] <= y2) {
                                ok = false;
                            }
                        }
                        if (ok) {
                            ans = max(ans, (y2 - y1) * (x2 - x1));
                        }
                    }
                }
            }
        }
        return ans;
    }
};