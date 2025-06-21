/*************************************************************************
    > File Name: Tk王国的括号.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-06-21 22:49
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
#define MULTICASE 0
void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    string ans;
    auto ck = [&](char c1, char c2) -> bool {
        if ('a' <= c1 && c1 <= 'm' && 'n' <= c2 && c2 <= 'z' && c1 - 'a' == 'z' - c2) {
            return true;
        } 
        if ('N' <= c1 && c1 <= 'Z' && 'A' <= c2 && c2 <= 'M' && 'Z' - c1 == c2 - 'A') {
            return true;
        } 
        return false;
    };
    for (char &c : s) {
        if (!ans.empty() && ck(ans.back(), c)) {
            ans.pop_back();
        } else {
            ans.push_back(c);
        }
    }
    cout << ans.size() << '\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(20);
    int T = 1;
#if MULTICASE
    cin >> T;
#endif
    while (T--) {
        solve();
    }
    return 0;
}