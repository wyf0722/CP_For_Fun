/*************************************************************************
    > File Name: D_Skibidi_Table.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-05-06 22:27
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
    int n, q;
    cin >> n >> q;
    while (q--) {
        string op;
        cin >> op;
        if (op == "->") {
            int x, y;
            cin >> x >> y;
            x--, y--;
            i64 d = 0;
            for (int i = n - 1; i >= 0; i--) {
                i64 len = 1LL << i;
                i64 cnt = len * len;
                int cx = x / len, cy = y / len;
                if (cx && cy) d += cnt;
                if (cx && !cy) d += cnt * 2;
                if (!cx && cy) d += cnt * 3;
                x %= len, y %= len;
            }
            cout << d + 1 << '\n';
        } else {
            i64 d;
            cin >> d;
            d--;
            int x = 0, y = 0;
            for (int i = n - 1; i >= 0; i--) {
                i64 len = 1LL << i;
                i64 cnt = len * len;
                i64 idx = d / cnt;
                if (idx == 1) x += len, y += len;
                if (idx == 2) x += len;
                if (idx == 3) y += len;
                d %= cnt;
            }
            cout << x + 1 << ' ' << y + 1 << '\n';
        }
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