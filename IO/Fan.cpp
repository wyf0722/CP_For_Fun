#include <bits/stdc++.h>

using namespace std;

// template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
// template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
 
// void dbg_out() { cout << endl; }
// template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
// #define debug(...) cout << '[' << __FILE__ << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define rrep(i, a, b) for (int i = a; i >= b; i--)
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

template <class T, class S = T>
S SUM(const vector<T>& a) {
    return accumulate(a.begin(), a.end(), S(0));
}

template <class T>
T MAX(const vector<T>& a) {
    return *max_element(a.begin(), a.end());
}

template <class T>
T MIN(const vector<T>& a) {
    return *min_element(a.begin(), a.end());
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
#define MULTICASE 0

template <typename F> struct reverse_comparator_t {
    F f;
    template <typename Arg1, typename Arg2> constexpr bool operator() (Arg1&& arg1, Arg2&& arg2) & {
        return f(std::forward<Arg2>(arg2), std::forward<Arg1>(arg1));
    }
    template <typename Arg1, typename Arg2> constexpr bool operator() (Arg1&& arg1, Arg2&& arg2) const& {
        return f(std::forward<Arg2>(arg2), std::forward<Arg1>(arg1));
    }
    template <typename Arg1, typename Arg2> constexpr bool operator() (Arg1&& arg1, Arg2&& arg2) && {
        return std::move(f)(std::forward<Arg2>(arg2), std::forward<Arg1>(arg1));
    }
    template <typename Arg1, typename Arg2> constexpr bool operator() (Arg1&& arg1, Arg2&& arg2) const&& {
        return std::move(f)(std::forward<Arg2>(arg2), std::forward<Arg1>(arg1));
    }
};

template <typename F> constexpr reverse_comparator_t<std::decay_t<F>> reverse_comparator(F&& f) {
    return { std::forward<F>(f) };
}

auto cmp = [] (pair<i64, i64> x, pair<i64, i64> y) {
    return x < y;
};
void solve() {
<<<<<<< HEAD
    string s;
    cin >> s;
    int n = s.size();
    int ans = 1;
    int flag = 0;
    for (int i = 1; i < n; i++) {
        if (s[i] != s[i - 1]) {
            ans += 1;
        }
        if (s[i - 1] == '0' && s[i] == '1') {
            flag = 1;
        }
    }
    // 出现01
    ans -= flag;
    cout << ans << endl;
=======
    int n, m; 
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n + 1);
    rep(i, 0, m) {
        int v, u, w; 
        cin >> v >> u >> w;
        adj[v].push_back({u, 2 * w});
        adj[u].push_back({v, 2 * w});
    }
    vector<i64> dis(n + 1, infLL);
    rep(i, 1, n + 1) {
        int w;
        cin >> w;
        adj[0].push_back({i, w});
    }
    dis[0] = 0LL;

    priority_queue<pair<i64, i64>, vector<pair<i64, i64>>, greater<pair<i64, i64>>> pq;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [d, x] = pq.top();
        pq.pop();
        if (d != dis[x]) continue;
        for (auto [y, w] : adj[x]) {
            if (d + w < dis[y]) {
                dis[y] = d + w;
                pq.push({dis[y], y});
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << dis[i] << " \n"[i == n];
    }
>>>>>>> 07e3d1d0317aef7cd5b9771ed16141153287c905
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