#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
#define MULTICASE 0
void solve() {
    int q;
    cin >> q;
    vector<vector<i64>> segs;
    while (q--) {
        i64 m, d;
        cin >> m >> d;
        segs.push_back({m - d, m + d});
    }
    sort(segs.begin(), segs.end());
    vector<vector<i64>> ans;
    bool ok = true;
    for (auto &seg : segs) {
        if (ans.empty()) {
            ans.push_back(seg);
        } else {
            if (ans.back()[1] >= seg[0]) {
                ans.back()[1] = min(ans.back()[1], seg[1]);
            } else {
                ok = false;
                break; 
            }
        }
    }
    if (!ok) {
        cout << -1 << endl;
    } else {
        cout << ans[0].back() << endl;
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