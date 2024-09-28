#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
#define MULTICASE 0
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(m));
    vector<int> max_i(n), max_j(m);
    int top = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> g[i][j];
            max_i[i] = max(max_i[i], g[i][j]);
            max_j[j] = max(max_j[j], g[i][j]);
            if (g[i][j] != 0) top++;
        }
    }
    int front = 0;
    for (int j = 0; j < m; j++) {
        front += max_j[j];
    }
    int left = 0;
    for (int i = 0; i < n; i++) {
        left += max_i[i];
    }
    cout << front << " " << left << " " << top << endl;
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