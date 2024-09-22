#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
#define MULTICASE 1
void solve() {
    int n;
    cin >> n;
    vector<i64> a(n);
    i64 sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    i64 target = sum * 2;
    if (target % n != 0) {
        cout << 0 << endl;
        return;
    }
    target /= n;
    unordered_map<i64, int> mp;
    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        ans += mp[target - a[i]];
        mp[a[i]]++;
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