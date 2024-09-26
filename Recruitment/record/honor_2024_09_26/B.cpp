#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
#define MULTICASE 0
void solve() {
    vector<vector<int>> g(9);
    for (int i = 0; i < 9; i++) {
        string s;
        cin >> s;
        s = s.substr(1, s.size() - 2);
        vector<int> row;
        int x = 0;
        for (auto ch : s) {
            if (ch == ',') {
                row.push_back(x);
                x = 0;
            } else {
                x = x * 10 + (ch - '0');
            }
        }
        row.push_back(x);
        g[i] = row;
    }

    auto valid = [&](int x, int y, int val) -> bool {
        for (int i = 0; i < 9; i++) if (g[i][y] == val) return false;
        for (int j = 0; j < 9; j++) if (g[x][j] == val) return false;
        int si = x / 3 * 3;
        int sj = y / 3 * 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (g[si + i][sj + j] == val) return false;
            }
        }
        return true;
    };
    vector<pair<int, int>> pos;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (g[i][j] == 0) {
                pos.emplace_back(i, j);
            }
        }
    }
    int n = pos.size();

    auto f = [&](auto &&self, int now) -> bool {
        if (now == n) {
            return true;
        }
        auto [x, y] = pos[now];
        for (int val = 1; val <= 9; val++) {
            if (valid(x, y, val)) {
                g[x][y] = val;
                if (self(self, now + 1)) {
                    return true;
                }
                g[x][y] = 0;
            }
        }
        return false;
    };
    f(f, 0);

    for (int i = 0; i < 9; i++) {
        string s = "{";
        for (int x : g[i]) {
            s += to_string(x) + ",";
        }
        s.back() = '}';
        cout << s << endl;
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