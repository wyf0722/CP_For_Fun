/*************************************************************************
    > File Name: A.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2026-02-04 00:16
************************************************************************/
#include <bits/stdc++.h>
#include <cctype>
using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#define debug(...) cout << '[' << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

using i64 = long long;
class Solution {
public:
    string reverseByType(string s) {
        int n = s.size();
        for (int i = 0, j = n - 1; i < j;) {
            if (islower(s[i]) && islower(s[j])) {
                swap(s[i++], s[j--]);
                continue;
            }
            if (!islower(s[i])) i++;
            if (!islower(s[j])) j--;
        }
        for (int i = 0, j = n - 1; i < j;) {
            if (!islower(s[i]) && !islower(s[j])) {
                swap(s[i++], s[j--]);
                continue;
            }
            if (islower(s[i])) i++;
            if (islower(s[j])) j--;
        }
        return s;
    }
};