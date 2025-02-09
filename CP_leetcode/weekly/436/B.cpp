/*************************************************************************
    > File Name: B.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-02-09 13:35
************************************************************************/
#include <bits/stdc++.h>
using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#define debug(...) cout << '[' << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

const int inf = 1e8;
class Solution {
public:
    vector<int> assignElements(vector<int>& groups, vector<int>& elements) {
        vector<int> idx(1e5 + 1, -1);
        for (int i = 0; i < elements.size(); i++) {
            if (idx[elements[i]] == -1) {
                idx[elements[i]] = i;
            }
        }
        vector<int> ans;
        auto ck = [&](int x) -> int {
            return idx[x] == -1 ? inf : idx[x];
        };
        for (int x : groups) {
            int r = inf;
            for (int i = 1; i * i <= x; i++) {
                if (x % i == 0) {
                    r = min(r, ck(i));
                    r = min(r, ck(x / i));
                }
            }
            ans.push_back(r == inf ? -1 : r);
        }
        return ans;
    }
};