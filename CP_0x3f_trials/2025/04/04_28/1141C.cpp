/*************************************************************************
    > File Name: C_Polycarp_Restores_Permutation.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-04-30 17:30
************************************************************************/
#include <bits/stdc++.h>
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
    vector<int> d(n);
    for (int i = 1; i < n; i++) {
        cin >> d[i];
        d[i] += d[i - 1];
    }
    int mn = ranges::min(d);
    for (int i = 0; i < n; i++) {
        d[i] += 1 - mn;
    }
    vector<int> ck(d);
    ranges::sort(ck);
    for (int i = 0; i < n; i++) {
        if (ck[i] != i + 1) {
            cout << -1 << '\n';
            return;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << d[i] << " \n"[i == n - 1];
    }
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