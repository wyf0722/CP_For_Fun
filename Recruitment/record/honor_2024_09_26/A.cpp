#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
#define MULTICASE 0
void solve() {
    int n;
    cin >> n;
    cout << (int)sqrt(n) << endl;
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