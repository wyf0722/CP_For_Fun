#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
#define MULTICASE 0
void solve() {
    int n, m;
    cin >> n >> m;
    unordered_set<int> has;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        has.insert(x);
    }
    int ans = 0;
    for (int now = 1; m >= now; now++) {
        if (has.find(now) == has.end()) {
            m -= now;
            ans++;
        }
    }
    cout << ans << endl;
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