/*************************************************************************
    > File Name: A.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-06-30 16:15
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
    vector<string> partitionString(string s) {
        int n = s.size();
        vector<string> ans;
        unordered_set<string> occur;
        for (int i = 0; i < n;) {
            int st = i;
            for (; i < n && occur.find(s.substr(st, i - st + 1)) != occur.end(); i++) {}
            if (i < n) {
                string w = s.substr(st, i - st + 1);
                ans.push_back(w);
                occur.insert(w);
                i++;
            }
        }
        return ans;
    }
};