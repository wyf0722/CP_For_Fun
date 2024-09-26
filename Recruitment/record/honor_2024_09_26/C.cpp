#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
#define MULTICASE 0
vector<int> get_vector_from_string() {
    string s;
    cin >> s;
    vector<int> input;
    int x = 0;
    for (auto ch : s) {
        if (ch == ',') {
            input.push_back(x);
            x = 0;
        } else {
            x = x * 10 + (ch - '0');
        }
    }
    input.push_back(x);
    return input;
}
void solve() {
    auto dis = get_vector_from_string();
    auto congestion = get_vector_from_string();
    auto light = get_vector_from_string();
    auto score = get_vector_from_string();
    int n = dis.size();
    vector<vector<int>> infos;
    for (int i = 0; i < n; i++) {
        vector<int> info(3);
        info[0] = i + 1;
        info[1] += (dis[i] - congestion[i]) / 10 + congestion[i] / 2 + light[i] / 2 * 15;
        info[2] = score[i];
        infos.push_back(info);
    }
    sort(infos.begin(), infos.end(), [&](auto &a, auto&b) -> bool {
        if (a[1] == b[1]) return a[2] > b[2];
        return a[1] < b[1];
    });
    vector<vector<int>> new_infos;
    new_infos.push_back(infos[0]);
    for (int i = 1; i < n; i++) {
        if (infos[i][1] == new_infos.back()[1]) continue;
        else new_infos.push_back(infos[i]);
    }
    if (infos.size() >= 2 && infos[0][1] + 60 > infos[1][1] && infos[0][2] < infos[1][2]) {
        cout << infos[1][0] << "," << infos[1][1] << endl;
    } else {
        cout << infos[0][0] << "," << infos[0][1] << endl;
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