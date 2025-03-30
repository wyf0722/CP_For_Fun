/*************************************************************************
    > File Name: B.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-03-30 13:24
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
    int longestPalindrome(string s, string t) {
        auto ck = [&](string str) -> bool {
            for (int i = 0, j = str.size() - 1; i < j; ++i, --j) {
                if (str[i] != str[j]) return false;
            }
            return true;
        };

        int ans = 1;
        for (int i = 0; i < s.size(); i++) {
            for (int j = i; j < s.size(); j++) {
                string str1 = s.substr(i, j - i + 1);
                if (ck(str1)) {
                    ans = max(ans, (int)str1.size());
                }
                for (int ii = 0; ii < t.size(); ii++) {
                    for (int jj = ii; jj < t.size(); jj++) {
                        string str2 = t.substr(ii, jj - ii + 1);
                        if (ck(str2)) {
                            ans = max(ans, (int)str2.size());
                        }

                        string str3 = str1 + str2;
                        if (ck(str3)) {
                            ans = max(ans, (int)str3.size());
                        }
                    }
                }
            }
        }
        return ans;
    }
};