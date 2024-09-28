#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
#define MULTICASE 0
void solve() {
    int n, m;
    cin >> n >> m;
    unordered_set<int> pos;
    pos.insert(1);
    pos.insert(n);
    unordered_map<int, vector<pair<int, int>>> g;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v, 0);
        g[v].emplace_back(u, 0);
        pos.insert(u);
        pos.insert(v);
    }
    priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<pair<i64, int>>> q;
    unordered_map<int, i64> dis;
    for (auto p : pos) {
        dis[p] = abs(p - 1);
        q.emplace(dis[p], p);
    }

    while (!q.empty()) {
        auto [d, x] = q.top();
        q.pop();
        pos.erase(x);
        if (d != dis[x]) {
            continue;
        }
        for (auto p : pos) {
            if (dis[p] > d + abs(p - x)) {
                q.emplace(d + abs(p - x), p);
                dis[p] = d + abs(p - x);
            }
        }
        for (auto [y, w] : g[x]) {
            if (dis[y] > dis[x]) {
                q.emplace(dis[x], y);
                dis[y] = dis[x];
            }
        }
    }

    cout << dis[n] << endl;
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