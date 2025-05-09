/*************************************************************************
    > File Name: B_Grid_Rotation.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-05-09 15:56
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
    vector<string> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    // 将a顺时针旋转90度
    auto rotate = [&](vector<string> &a) -> vector<string> {
        vector<string> r(n, string(n, '0'));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                r[i][j] = a[n - 1 - j][i]; // 顺时针旋转90度的公式：r[i][j] = a[n - 1 - j][i]
            }
        }
        return r;
    };
    int ans = n * n;
    auto f = [&](vector<string> &x, vector<string> &y) -> int {
        int r = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (x[i][j] != y[i][j]) r++;
            }
        }
        return r;
    };
    ans = min(ans, f(a, b));
    a = rotate(a);
    ans = min(ans, f(a, b) + 1);
    a = rotate(a);
    ans = min(ans, f(a, b) + 2);
    a = rotate(a);
    ans = min(ans, f(a, b) + 3);
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