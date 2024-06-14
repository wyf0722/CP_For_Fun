#include <bits/stdc++.h>

using namespace std;

// template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
// template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
 
// void dbg_out() { cout << endl; }
// template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
// #define debug(...) cout << '[' << __FILE__ << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

#define all(x) begin(x), end(x)
#define rall(x) begin(x), end(x)
// loops
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define rep(a) F0R(_, a)
#define each(a, x) for (auto &a : x)
using i64 = long long;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<i64, i64>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<ll>>;
using vpii = vector<pii>;
using vpll = vector<pll>;
const int inf = INT_MAX / 2 - 100;
const i64 infLL = LLONG_MAX / 3;
const int MOD = 1e9 + 7;
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};
template<typename T> using min_heap=priority_queue<T,vector<T>,greater<T>>;
template<typename T> using max_heap=priority_queue<T>;

template <class T>
void mkuni(vector<T>& v) {
    sort(all(v));
    v.erase(unique(all(v)), v.end());
}

template <class T>
int lwb(vector<T>& a, const T& b) {
    return int(lower_bound(all(a), b) - begin(a));
}

template <class T>
int upb(vector<T>& a, const T& b) {
    return int(upper_bound(all(a), b) - begin(a));
}

constexpr int popcount(int x) {
    return __builtin_popcount(x);
}

constexpr int topbit(int x) {
    return x == 0 ? 0 : 31 - __builtin_clz(x);
}

template <class T, class U>
void safeErase(T& t, const U& u) {
    auto it = t.find(u);
    assert(it != end(t));
    t.erase(it);
}

template<class T, class U>
T fstTrue(T lo, T hi, U f) {
    ++hi;
    assert(lo <= hi);  // assuming f is increasing
    while (lo < hi) {  // find first index such that f is true
        T mid = lo + (hi - lo) / 2;
        f(mid) ? hi = mid : lo = mid + 1;
    }
    return lo;
}

template<class T, class U>
T lstTrue(T lo, T hi, U f) {
    --lo;
    assert(lo <= hi);  // assuming f is decreasing
    while (lo < hi) {  // find first index such that f is true
        T mid = lo + (hi - lo + 1) / 2;
        f(mid) ? lo = mid : hi = mid - 1;
    }
    return lo;
}

inline void add_mod(int& x, int y) { x += y; if (x >= MOD) x -= MOD; }
inline void sub_mod(int& x, int y) { x += MOD - y; if (x >= MOD) x -= MOD; }

template <class T>
bool chmin(T& a, const T& b) {
    return b < a ? a = b, 1 : 0;
}  // set a = min(a,b)
template <class T>
bool chmax(T& a, const T& b) {
    return a < b ? a = b, 1 : 0;
}  // set a = max(a,b)

#ifdef FAN_DEBUG
#include "Debug/template_cpp20_std.cpp"
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
struct DSU {
    std::vector<int> f, siz;
     
    DSU() {}
    DSU(int n) {
        init(n);
    }
     
    void init(int n) {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }
     
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
     
    bool same(int x, int y) {
        return find(x) == find(y);
    }
     
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
     
    int size(int x) {
        return siz[find(x)];
    }
};
#define MULTICASE 1
void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    FOR(i, 0, n) {
        cin >> g[i];
    }
    
    int N = n * m;
    DSU dsu(N);
    auto get_idx = [&](int i, int j) -> int {
        return i * m + j;
    };
    FOR(i, 0, n) {
        FOR(j, 0, m) {
            if (g[i][j] != '#') continue;
            if (i + 1 < n && g[i + 1][j] == '#') dsu.merge(get_idx(i, j), get_idx(i + 1, j));
            if (j + 1 < m && g[i][j + 1] == '#') dsu.merge(get_idx(i, j), get_idx(i, j + 1));
        }
    }

    vi vis(N, -1);
    int ans = 0;
    FOR(r, 0, n) {
        int res = 0;
        FOR(i, 0, m) {
            if (g[r][i] == '.') res++;
            FOR(rr, max(0, r - 1), min(n - 1, r + 1) + 1) {
                if (g[rr][i] == '#') {
                    int root = dsu.find(get_idx(rr, i));
                    if (vis[root] != r) {
                        vis[root] = r;
                        res += dsu.size(root);
                    }
                }
            }
        }
        chmax(ans, res);
    }

    fill(all(vis), -1);
    FOR(c, 0, m) {
        int res = 0;
        FOR(i, 0, n) {
            if (g[i][c] == '.') res++;
            FOR(cc, max(0, c - 1), min(m - 1, c + 1) + 1) {
                if (g[i][cc] == '#') {
                    int root = dsu.find(get_idx(i, cc));
                    if (vis[root] != c) {
                        vis[root] = c;
                        res += dsu.size(root);
                    }
                }
            }
        }
        chmax(ans, res);
    }

    cout << ans << endl;
}

// 官方解答
// void solve() {
//     int n, m;
//     cin >> n >> m;
//     vector<string> g(n);
//     FOR(i, 0, n) {
//         cin >> g[i];
//     }

//     // 考虑每个联通分量的x区间和y区间
//     vi R(n + 1), C(m + 1);
//     vi freeR(n + 1), freeC(m + 1);
//     vvi vis(n, vi(m));
//     int sz = 0;
//     int minR = n, maxR = -1;
//     int minC = m, maxC = -1;

//     auto dfs = [&](auto &&self, int i, int j) -> void {
//         vis[i][j] = 1;
//         sz++;
//         chmax(maxR, i);
//         chmin(minR, i);
//         chmax(maxC, j);
//         chmin(minC, j);
//         FOR(d, 0, 4) {
//             int ni = i + dx[d];
//             int nj = j + dy[d];
//             if (0 <= ni && ni < n && 0 <= nj && nj < m && !vis[ni][nj] && g[ni][nj] == '#') {
//                 self(self, ni, nj);
//             }
//         }
//     };

//     FOR(i, 0, n) {
//         FOR(j, 0, m) {
//             if (g[i][j] == '.') {
//                 freeR[i]++;
//                 freeC[j]++;
//                 continue;
//             }
//             if (vis[i][j]) continue;
//             sz = 0;
//             minR = n, maxR = -1;
//             minC = m, maxC = -1;

//             dfs(dfs, i, j);

//             // debug(sz);
//             // 可以覆盖哪些区间 ？
//             chmin(minR, max(minR - 1, 0));
//             chmax(maxR, min(maxR + 1, n - 1));
//             chmin(minC, max(minC - 1, 0));
//             chmax(maxC, min(maxC + 1, m - 1));

//             R[minR] += sz;
//             R[maxR + 1] -= sz;
//             C[minC] += sz;
//             C[maxC + 1] -= sz;
//         }
//     }

//     int ans = 0;
//     FOR(i, 0, n) {
//         if (i) R[i] += R[i - 1];
//         chmax(ans, freeR[i] + R[i]);
//     }
//     FOR(j, 0, m) {
//         if (j) C[j] += C[j - 1];
//         chmax(ans, freeC[j] + C[j]);
//     }
//     cout << ans << endl;
// }


// 并查集 + 差分
// void solve() {
//     int n, m;
//     cin >> n >> m;
//     vector<string> g(n);
//     FOR(i, 0, n) {
//         cin >> g[i];
//     }
//     int N = n * m;
//     // 考虑每个联通分量的x区间和y区间
//     vi freeR(n + 1), freeC(m + 1);
//     vi maxR(N, -1), maxC(N, -1), minR(N, n), minC(N, m);
//     DSU dsu(N);

//     FOR(i, 0, n) {
//         FOR(j, 0, m) {
//             if (i + 1 < n && g[i][j] == '#' && g[i + 1][j] == '#') dsu.merge(i * m + j, (i + 1) * m + j);
//             if (j + 1 < m && g[i][j] == '#' && g[i][j + 1] == '#') dsu.merge(i * m + j, i * m + j + 1);
//         }
//     }

//     FOR(i, 0, n) {
//         FOR(j, 0, m) {
//             if (g[i][j] == '.') {
//                 freeR[i]++;
//                 freeC[j]++;
//             } else {
//                 int root = dsu.find(i * m + j);
//                 chmax(maxR[root], min(n - 1, i + 1));
//                 chmax(maxC[root], min(m - 1, j + 1));
//                 chmin(minR[root], max(0, i - 1));
//                 chmin(minC[root], max(0, j - 1));
//             }
//         }
//     }
//     int ans = 0;
//     vi R(n + 1), C(m + 1);
//     FOR(i, 0, N) {
//         if (dsu.find(i) == i && g[i / m][i % m] == '#') {
//             int sz = dsu.size(i);
//             R[minR[i]] += sz;
//             R[maxR[i] + 1] -= sz;
//             C[minC[i]] += sz;
//             C[maxC[i] + 1] -= sz;
//         }
//     }
//     FOR(i, 0, n) {
//         if (i) R[i] += R[i - 1];
//         chmax(ans, R[i] + freeR[i]);
//     }
//     FOR(j, 0, m) {
//         if (j) C[j] += C[j - 1];
//         chmax(ans, C[j] + freeC[j]);
//     }
//     cout << ans << endl;
// }
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