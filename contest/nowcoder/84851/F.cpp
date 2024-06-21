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
int MOD = 1e9 + 7;
int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};
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
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    FOR(i, 0, n) {
        cin >> g[i];
    }
    vi C(m);
    FOR(i, 0, m) {
        cin >> C[i];
    }

    auto flatten = [&](int x, int y) -> int {
        return x * m + y;
    };

    vector<vector<pii>> path((n + 1) * m);
    FOR(i, 0, n) {
        FOR(j, 0, m) {
            FOR(d, 0, 4) {
                int ni = i + dx[d], nj = j + dy[d];
                if (0 <= ni && ni < n && 0 <= nj && nj < m && g[ni][nj] == '.') {
                    path[flatten(i, j)].emplace_back(flatten(ni, nj), 0);
                }
            }
            // 加的点可以到改列所有位置
            path[flatten(n, j)].emplace_back(flatten(i, j), 0);
            // 可以花费C[j + 1]到下一列
            if (j + 1 < m) path[flatten(i, j)].emplace_back(flatten(n, j + 1), C[j + 1]);
        }
    }

    vi dis((n + 1) * m, inf);
    min_heap<pii> heap;
    heap.emplace(0, 0);
    heap.emplace(C[0], flatten(n, 0));
    dis[0] = 0;
    dis[flatten(n, 0)] = C[0];
    while (!heap.empty()) {
        auto [d, cur_idx] = heap.top();
        heap.pop();
        if (d != dis[cur_idx]) continue;
        for (auto [nxt_idx, w] : path[cur_idx]) {
            if (dis[nxt_idx] > dis[cur_idx] + w) {
                dis[nxt_idx] = dis[cur_idx] + w;
                heap.emplace(dis[nxt_idx], nxt_idx);
            }
        }
    }
    cout << dis[flatten(n - 1, m - 1)] << endl;
}

// /**
//  * https://github.com/the-tourist/algo/blob/master/graph/dijkstra.cpp
// */
// template <typename T>
// class graph {
//    public:
//     struct edge {
//         int from;
//         int to;
//         T cost;
//     };

//     vector<edge> edges;
//     vector<vector<int>> g;
//     int n;

//     graph(int _n) : n(_n) { g.resize(n); }

//     virtual int add(int from, int to, T cost) = 0;
// };

// // 有向图
// template <typename T>
// class digraph : public graph<T> {
//    public:
//     using graph<T>::edges;
//     using graph<T>::g;
//     using graph<T>::n;

//     digraph(int _n) : graph<T>(_n) {}

//     int add(int from, int to, T cost = 1) {
//         assert(0 <= from && from < n && 0 <= to && to < n);
//         int id = (int)edges.size();
//         g[from].push_back(id);
//         edges.push_back({from, to, cost});
//         return id;
//     }

//     digraph<T> reverse() const {
//         digraph<T> rev(n);
//         for (auto& e : edges) {
//             rev.add(e.to, e.from, e.cost);
//         }
//         return rev;
//     }
// };

// // 无向图
// template <typename T>
// class undigraph : public graph<T> {
//    public:
//     using graph<T>::edges;
//     using graph<T>::g;
//     using graph<T>::n;

//     undigraph(int _n) : graph<T>(_n) {}

//     int add(int from, int to, T cost = 1) {
//         assert(0 <= from && from < n && 0 <= to && to < n);
//         int id = (int)edges.size();
//         g[from].push_back(id);
//         g[to].push_back(id);
//         edges.push_back({from, to, cost});
//         return id;
//     }
// };

// template <typename T>
// vector<T> dijkstra(const graph<T>& g, int start) {
//     assert(0 <= start && start < g.n);
//     vector<T> dist(g.n, numeric_limits<T>::max());
//     priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> s;
//     dist[start] = 0;
//     s.emplace(dist[start], start);
//     while (!s.empty()) {
//         T expected = s.top().first;
//         int i = s.top().second;
//         s.pop();
//         if (dist[i] != expected) {
//             continue;
//         }
//         for (int id : g.g[i]) {
//             auto& e = g.edges[id];
//             int to = e.from ^ e.to ^ i;
//             if (dist[i] + e.cost < dist[to]) {
//                 dist[to] = dist[i] + e.cost;
//                 s.emplace(dist[to], to);
//             }
//         }
//     }
//     return dist;
//     // returns numeric_limits<T>::max() if there's no path
// }
// void solve() {
//     int n, m;
//     cin >> n >> m;
//     vector<string> g(n);
//     FOR(i, 0, n) {
//         cin >> g[i];
//     }
//     vi C(m);
//     FOR(i, 0, m) {
//         cin >> C[i];
//     }

//     auto flatten = [&](int x, int y) -> int {
//         return x * m + y;
//     };

//     digraph<int> path((n + 1) * m);
//     FOR(i, 0, n) {
//         FOR(j, 0, m) {
//             FOR(d, 0, 4) {
//                 int ni = i + dx[d], nj = j + dy[d];
//                 if (0 <= ni && ni < n && 0 <= nj && nj < m && g[ni][nj] == '.') {
//                     path.add(flatten(i, j), flatten(ni, nj), 0);
//                 }
//             }
//             // 加的点可以到改列所有位置
//             path.add(flatten(n, j), flatten(i, j), 0);
//             // 可以花费C[j + 1]到下一列
//             if (j + 1 < m) path.add(flatten(i, j), flatten(n, j + 1), C[j + 1]);

//         }
//     }
    
//     path.add(flatten(0, 0), flatten(n, 0), C[0]);
//     auto dis = dijkstra(path, flatten(0, 0));
//     cout << dis[flatten(n - 1, m - 1)] << endl;
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