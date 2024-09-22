#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
#define MULTICASE 1
void solve() {
    int n;
    cin >> n;
    vector<i64> a(n);
    unordered_set<i64> s;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] = abs(a[i]);
        s.insert(a[i]);
    }
    if (s.size() < n || s.count(0LL)) {
        cout << "yes" << endl;
        return;
    }
    // 两组差值和相同
    for (int mask = 0; mask < (1 << n); mask++) {
        i64 sum = 0;
        for (int i = 0; i < n; i++) if (mask >> i & 1) sum += a[i];
        for (int s = mask & (mask - 1); s; s = (s - 1) & mask) {
            i64 cur = 0;
            for (int i = 0; i < n; i++) {
                if (s >> i & 1) cur += a[i];
            }
            if (sum == cur * 2) {
                cout << "yes" << endl;
                return;
            }
        }
    }
    cout << "no" << endl;
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