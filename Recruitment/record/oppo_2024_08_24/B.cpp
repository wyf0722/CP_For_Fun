#include <bits/stdc++.h>
using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
 
void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#define debug(...) cout << '[' << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

#define MULTICASE 0
void solve() {
    int n;
    cin >> n;
    unordered_map<int, int> mp;
    vector<int> cnt(n + 1);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mp[a[i]]++;
        if (a[i] <= n) cnt[a[i]] = 1;
    }
    int mx = -1;
    for (int i = 1; i <= n; i++) {
        if (cnt[i] && cnt[i - 1]) cnt[i] = 1, mx = i;
        else cnt[i] = 0;
    }
    vector<int> ans;
    for (int x : a) {
        if (x > mx) ans.push_back(mx + 1);
        else {
            if (mp[x] >= 2) ans.push_back(mx + 1);
            else ans.push_back(x);
        }
    }
    for (int i = 0; i < n; i++) cout << ans[i] << " \n"[i == n - 1];
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