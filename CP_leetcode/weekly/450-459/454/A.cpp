/*************************************************************************
    > File Name: A.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-06-19 23:13
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
    string generateTag(string caption) {
        string ans{"#"};
        int n = caption.size();
        for (int i = 0; i < n;) {
            int st = i;
            for (; i < n && caption[i] != ' '; i++) {}
            string w = caption.substr(st, i - st);
            for (char &c : w) {
                c = tolower(c);
            }
            w[0] = toupper(w[0]);
            ans += w;
            i++;
        }
        ans = ans.substr(0, 100);
        ans[1] = tolower(ans[1]);
        return ans;
    }
};