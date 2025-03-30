/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-03-30 23:05
************************************************************************/
#include <bits/stdc++.h>
using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#define debug(...) cout << '[' << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

using i64 = long long;
#define MULTICASE 1
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    string s;
    cin >> s;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '>') {
            if (a[i] <= 0) {
                ans++;
                a[i] = 1;
            }
        } else if (s[i] == '<') {
            if (a[i] >= 0) {
                ans++;
                a[i] = -1;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (s[i] == 'Z') {
            if (a[i - 1] < 0) {
                if (a[i] >= 0) {
                    ans++;
                    a[i] = -1;
                }
            } else {
                if (a[i] <= 0) {
                    ans++;
                    a[i] = 1;
                }
            }
        }
    }
    cout << ans << '\n';
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