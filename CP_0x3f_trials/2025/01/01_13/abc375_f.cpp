#include <bits/stdc++.h>

using namespace std;

// template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
// template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
 
// void dbg_out() { cout << endl; }
// template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
// #define debug(...) cout << '[' << __FILE__ << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

using i64 = long long;
const int inf = INT_MAX / 2 - 100;
const i64 infLL = LLONG_MAX / 3;
constexpr int MOD = 998244353; // 998244353 1000000007
int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};
template <class T> using V = vector<T>;
template<typename T> using min_heap=priority_queue<T,vector<T>,greater<T>>;
template<typename T> using max_heap=priority_queue<T>;

constexpr int popcount(int x) { return __builtin_popcount(x); }
constexpr int topbit(int x) { return x == 0 ? 0 : 31 - __builtin_clz(x); }

template <class T> bool chmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }  // set a = min(a,b)
template <class T> bool chmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }  // set a = max(a,b)

template<class T, class U> T fstTrue(T lo, T hi, U f) { ++hi; assert(lo <= hi); while (lo < hi) { T mid = lo + (hi - lo) / 2; f(mid) ? hi = mid : lo = mid + 1; } return lo; }
template<class T, class U> T lstTrue(T lo, T hi, U f) { --lo; assert(lo <= hi); while (lo < hi) { T mid = lo + (hi - lo + 1) / 2; f(mid) ? lo = mid : hi = mid - 1; } return lo; }

#ifdef FAN_DEBUG
#include "../Util_For_Debug/template_cpp20_std.cpp"
#else
#define debug(...)
#endif

/***
 *
 *   █████▒█    ██  ▄████▄   ██ ▄█▀       ██████╗ ██╗   ██╗ ██████╗
 * ▓██   ▒ ██  ▓██▒▒██▀ ▀█   ██▄█▒        ██╔══██╗██║   ██║██╔════╝
 * ▒████ ░▓██  ▒██░▒▓█    ▄ ▓███▄░        ██████╔╝██║   ██║██║  ███╗
 * ░▓█▒  ░▓▓█  ░██░▒▓▓▄ ▄██▒▓██ █▄        ██╔══██╗██║   ██║██║   ██║
 * ░▒█░   ▒▒█████▓ ▒ ▓███▀ ░▒██▒ █▄       ██████╔╝╚██████╔╝╚██████╔╝
 *  ▒ ░   ░▒▓▒ ▒ ▒ ░ ░▒ ▒  ░▒ ▒▒ ▓▒       ╚═════╝  ╚═════╝  ╚═════╝
 *  ░     ░░▒░ ░ ░   ░  ▒   ░ ░▒ ▒░
 *  ░ ░    ░░░ ░ ░ ░        ░ ░░ ░
 *           ░     ░ ░      ░  ░
 */
#define MULTICASE 0
void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<i64>> g(n, vector<i64>(n, infLL));
    for (int i = 0; i < n; i++) {
        g[i][i] = 0;
    }
    vector<tuple<int, int, i64>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        i64 w;
        cin >> u >> v >> w;
        u--, v--;
        edges.push_back({u, v, w});
        g[u][v] = w;
        g[v][u] = w;
    }

    vector<vector<int>> qs;
    for (int i = 0; i < q; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int edge_id;
            cin >> edge_id;
            edge_id--;
            auto [u, v, _] = edges[edge_id];
            g[u][v] = infLL;
            g[v][u] = infLL;
            qs.push_back({op, edge_id});
        } else {
            int x, y;
            cin >> x >> y;
            x--, y--;
            qs.push_back({op, x, y});
        }
    }
    // debug(qs);

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                chmin(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }

    auto addEdge = [&](int x, int y, i64 w) -> void {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                chmin(g[i][j], g[i][x] + g[y][j] + w);
                chmin(g[i][j], g[i][y] + g[x][j] + w);
            }
        }
    };
    vector<i64> ans;
    for (int i = qs.size() - 1; i >= 0; i--) {
        if (qs[i].size() == 2) {
            auto [x, y, w] = edges[qs[i][1]];
            addEdge(x, y, w);
        } else {
            int x = qs[i][1], y = qs[i][2];
            i64 res = g[x][y];
            ans.push_back(res == infLL ? -1 : res);
        }
        // debug(g);
    }
    for (int i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i] << endl;
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