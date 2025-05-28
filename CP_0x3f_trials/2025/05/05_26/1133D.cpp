/*************************************************************************
    > File Name: D_Zero_Quantity_Maximization.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-05-28 14:15
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
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    map<pair<int, int>, int> p;
    int zero = 0, common = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            if (b[i] == 0) {
                common += 1;
            }
        } else if (b[i] == 0) {
            zero++;
        } else {
            int flag = 1;
            if (1LL * a[i] * b[i] < 0) {
                flag = -1;
            }
            a[i] = abs(a[i]);
            b[i] = abs(b[i]);
            int g = gcd(a[i], b[i]);
            a[i] /= g;
            b[i] /= g;
            p[{flag * a[i], b[i]}] += 1;
        }
    }
    for (auto &[_, c] : p) {
        zero = max(zero, c);
    }
    cout << zero + common << endl;
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