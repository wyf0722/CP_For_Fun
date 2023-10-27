#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
const i64 mod = 1e9 + 7;

#ifdef LOCAL
#include "./DebugTemplate/debug.h"
#else
#define debug(...)
#endif

/*###########################################
#############################################
#######      Solution    ####################
#############################################
#############################################*/

 void solve() {
    int n;
    cin >> n;
    vector<int> A(2 * n);
    for (int i = 0; i < 2 * n; i++) cin >> A[i];
    vector<int> a, b;
    debug(a, b);
    for (int i = 0; i < n; i++) {
        while (a.size() && A[i] < a.back()) {
            a.pop_back();
            b.pop_back();
        }
        a.push_back(A[i]);
        b.push_back(A[i + n]);
    }
    int i = upper_bound(a.begin(), a.end(), a[0]) - a.begin();
    int mn = *min_element(b.begin(), b.begin() + i);
    if (mn <= a[0]) {
        cout << a[0] << " " << mn << endl;
        return;
    }
    int l = lower_bound(a.begin(), a.end(), b[0]) - a.begin();
    int r = upper_bound(a.begin(), a.end(), b[0]) - a.begin();
    debug(a, b);
    debug(l, r);
    vector<int> s1;
    for (int i = 0; i < l; i++) s1.push_back(a[i]);
    for (int i = 0; i < l; i++) s1.push_back(b[i]);
    vector<int> s2;
    for (int i = 0; i < r; i++) s2.push_back(a[i]);
    for (int i = 0; i < r; i++) s2.push_back(b[i]);
    
    for (int c: min(s1, s2)) {
        cout << c << " ";
    }
    cout << endl;
 }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    bool MULTIPLE_TEST_CASE = 0;
    if (MULTIPLE_TEST_CASE) { cin >> T; }
    while (T--) {
        solve();
    }
    return 0;
}

