/*************************************************************************
    > File Name: B.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2024-12-15 13:19
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
    double maxAmount(string initialCurrency, vector<vector<string>>& pairs1, vector<double>& rates1, vector<vector<string>>& pairs2, vector<double>& rates2) {
        unordered_map<string, double> day0;
        day0[initialCurrency] = 1;
        auto f = [&](vector<vector<string>> p, vector<double> rate, unordered_map<string, double> cur) -> unordered_map<string, double> {
            unordered_map<string, vector<pair<string, double>>> g;
            for (int i = 0; i < p.size(); i++) {
                g[p[i][0]].push_back({p[i][1], rate[i]});
                g[p[i][1]].push_back({p[i][0], 1.0 / rate[i]});
            }
            unordered_map<string, double> nxt(cur);
            queue<string> q;
            for (auto &[k, v] : cur) {
                if (v != 0) q.push(k);
            }
            while (!q.empty()) {
                auto x = q.front();
                q.pop();
                for (auto &[y, r] : g[x]) {
                    if (nxt[y] < nxt[x] * r) {
                        nxt[y] = nxt[x] * r;
                        q.push(y);
                    }
                }
            }
            return nxt;
        };

        auto day1 = f(pairs1, rates1, day0);
        auto day2 = f(pairs2, rates2, day1);
        return day2[initialCurrency];
    }
};