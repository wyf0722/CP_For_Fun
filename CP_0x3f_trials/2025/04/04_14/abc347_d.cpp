/*************************************************************************
    > File Name: D_Popcount_and_XOR.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-04-15 12:26
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
    int a, b;
    i64 c;
    cin >> a >> b >> c;
    // 为1的必须是10
    i64 x = 0, y = 0;
    int must = __builtin_popcountll(c);
    if ((a + b - must) % 2 || must > a + b) {
        cout << -1 << '\n';
        return;
    }
    // musta + bit = a
    // mustb + bit = b
    // musta + mustb = must
    // bit = (a + b - must) / 2
    int bit = (a + b - must) / 2;
    a -= bit;
    b -= bit;
    for (int i = 0; i < 60; i++) {
        if ((c >> i & 1) == 0 && bit) {
            x |= 1LL << i;
            y |= 1LL << i;
            bit--;
        }
        if (c >> i & 1) {
            if (a) {
                x |= 1LL << i;
                a--;
            } else {
                y |= 1LL << i;
                b--;
            }
        }
    }
    if (a != 0 || b != 0 || bit != 0) {
        cout << -1 << '\n';
        return;
    }
    cout << x << ' ' << y << '\n';
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