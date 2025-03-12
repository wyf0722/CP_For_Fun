#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    
    vector<bool> has(n - 1);
    
    function<int(int,int)> dfs = [&](int x, int fa) {
        int size = 1;
        vector<bool> f(n - 1);
        f[0] = true;
        
        for (int y : g[x]) {
            if (y == fa) continue;
            int sz = dfs(y, x);
            for (int j = n - 2; j >= sz; j--) {
                f[j] = f[j] || f[j - sz];
            }
            size += sz;
        }
        
        int sz = n - size;
        for (int j = n - 2; j >= sz; j--) {
            f[j] = f[j] || f[j - sz];
        }
        
        for (int b = 0; b < n - 1; b++) {
            if (f[b]) has[b] = true;
        }
        
        return size;
    };
    
    dfs(0, -1);
    has[0] = false;
    
    int ans = 0;
    for (bool x : has) if (x) ans++;
    cout << ans << "\n";
    
    for (int i = 0; i < n - 1; i++) {
        if (has[i]) {
            cout << i << " " << n - 1 - i << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t = 1;
    while (t--) solve();
    
    return 0;
}