#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
#define MULTICASE 0
int MX = 1e6;
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<vector<int>> rec(MX + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (rec[a[i]].size() == 0) {
            int x = a[i];
            for (int j = 2; j * j <= x; j++) {
                if (x % j) continue;
                rec[a[i]].push_back(j);
                while (x % j == 0) x /= j;
            }
            if (x != 1) rec[a[i]].push_back(x);
        }
    }
    int ans = 1;
    unordered_map<int, int> mp;
    int bad = 0;
    for (int i = 0, j = 0; j < n; j++) {
        for (int p : rec[a[j]]) {
            mp[p]++;
            if (mp[p] == 2) bad++;
        }
        while (bad) {
            for (int p : rec[a[i]]) {
                mp[p]--;
                if (mp[p] == 1) bad--;
            }
            i++;
        }
        ans = max(ans, j - i + 1);
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