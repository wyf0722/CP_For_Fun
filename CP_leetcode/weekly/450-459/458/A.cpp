/*************************************************************************
    > File Name: A.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-07-15 00:39
************************************************************************/
#include <bits/stdc++.h>
#include <cctype>
using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#define debug(...) cout << '[' << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

class Solution {
public:
    string processStr(string s) {
        string ans = "";
        for (auto &c : s) {
            if (islower(c)) {
                ans += c;
            } else if (c == '*') {
                if (!ans.empty()) {
                    ans.pop_back();
                }
            } else if (c == '#') {
                ans += ans;
            } else {
                ranges::reverse(ans);
            }
        }
        return ans;
    }
};