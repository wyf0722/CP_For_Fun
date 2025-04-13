/*************************************************************************
    > File Name: B.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-04-13 12:46
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
    string smallestPalindrome(string s) {
        vector<int> cnt(26, 0);
        for (auto c : s) cnt[c - 'a']++;
        int n = s.size();
        string ans(n, '?');
        if (n & 1) {
            for (int i = 25; i >= 0; i--) {
                if (cnt[i] & 1) {
                    ans[n / 2] = 'a' + i;
                    cnt[i]--;
                }
            }
        }
        for (int i = 0; i < n / 2; i++) {
            for (int j = 0; j < 26; j++) {
                if (cnt[j]) {
                    ans[i] = ans[n - 1 - i] = 'a' + j;
                    cnt[j] -= 2;
                    break;
                }
            }
        }
        return ans;
    }
};