#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
#define MULTICASE 0
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> cnt(m), mx(m, 0), mn(m, 1000);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            if (isupper(s[j])) {
                s[j] = tolower(s[j]);
            }
            int score = s[j] - 'a' + 1;
            cnt[j] += score;
            mx[j] = max(mx[j], score);
            mn[j] = min(mn[j], score);
        }
    }
    for (int i = 0; i < m; i++) {
        cnt[i] = cnt[i] - mx[i] - mn[i];
    }
    vector<int> ids(m);
    for (int &x : cnt) x = (x + n - 3) / (n - 2);
    iota(ids.begin(), ids.end(), 0);
    sort(ids.begin(), ids.end(), [&](int x, int y) {
        if (cnt[x] == cnt[y]) return x < y;
        return cnt[x] < cnt[y];
    });
    for (int i = 0; i < m; i++) {
        cout << ids[i] + 1 << " \n"[i == m - 1];
    }
    for (int i = 0; i < m; i++) {
        cout << char('a' + cnt[ids[i]] - 1) << " \n"[i == m - 1];
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