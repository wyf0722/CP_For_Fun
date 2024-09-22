#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
#define MULTICASE 0
void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> pdd;
    vector<string> no_pdd;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        if (s.find("PDD") != -1) {
            pdd.push_back(s);
        } else {
            no_pdd.push_back(s);
        }
    }
    sort(pdd.begin(), pdd.end());
    sort(no_pdd.begin(), no_pdd.end());
    for (auto x : no_pdd) pdd.push_back(x);
    for (int i = 0; i < m; i++) cout << pdd[i] << endl;
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