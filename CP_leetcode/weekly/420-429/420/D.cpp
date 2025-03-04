#include <bits/stdc++.h>

using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#define debug(...) cout << '[' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

#define all(x) begin(x), end(x)
#define rall(x) begin(x), end(x)
// loops
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
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
constexpr int MOD = 1000000007; // 998244353 1000000007
int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};
template<typename T> using min_heap=priority_queue<T,vector<T>,greater<T>>;
template<typename T> using max_heap=priority_queue<T>;

constexpr int popcount(int x) { return __builtin_popcount(x); }
constexpr int topbit(int x) { return x == 0 ? 0 : 31 - __builtin_clz(x); }

inline void add_mod(int& x, int y) { x += y; if (x >= MOD) x -= MOD; }
inline void sub_mod(int& x, int y) { x += MOD - y; if (x >= MOD) x -= MOD; }

template <class T> bool chmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }  // set a = min(a,b)
template <class T> bool chmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }  // set a = max(a,b)

template <class T> void mkuni(vector<T>& v) { sort(all(v)); v.erase(unique(all(v)), v.end()); }
template <class T> int lwb(vector<T>& a, const T& b) { return int(lower_bound(all(a), b) - begin(a)); }
template <class T> int upb(vector<T>& a, const T& b) { return int(upper_bound(all(a), b) - begin(a)); }
template <class T, class U> void safeErase(T& t, const U& u) { auto it = t.find(u); assert(it != end(t)); t.erase(it); }

template<class T, class U> T fstTrue(T lo, T hi, U f) { ++hi; assert(lo <= hi); while (lo < hi) { T mid = lo + (hi - lo) / 2; f(mid) ? hi = mid : lo = mid + 1; } return lo; }
template<class T, class U> T lstTrue(T lo, T hi, U f) { --lo; assert(lo <= hi); while (lo < hi) { T mid = lo + (hi - lo + 1) / 2; f(mid) ? lo = mid : hi = mid - 1; } return lo; }

/***
 * \U0001d4fd\U0001d4f1\U0001d4ee \U0001d4fc\U0001d4f8\U0001d4f5\U0001d4fe\U0001d4fd\U0001d4f2\U0001d4f8\U0001d4f7 \U0001d4f8\U0001d4ef \U0001d500\U0001d502\U0001d4ef0722
 */

// 随机模数
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int x, int y) {
    return uniform_int_distribution<int>(x, y)(rng);
}

int SINGLE_MOD = 998244353 + rnd(0, 1e9), SINGLE_BASE = 233 + rnd(0, 1e3);

// 单模数
struct StringHash {
    vector<long long> P, H;
    int MOD, BASE;

    StringHash() {}

    StringHash(string &s, int m = SINGLE_MOD, int b = SINGLE_BASE) {
        MOD = m;
        BASE = b;
        int n = s.size();
        P.resize(n + 1);
        P[0] = 1;
        for (int i = 1; i <= n; i++) P[i] = P[i - 1] * BASE % MOD;
        H.resize(n + 1);
        H[0] = 0;
        for (int i = 1; i <= n; i++) H[i] = (H[i - 1] * BASE + (s[i - 1] ^ 7)) % MOD;
    }

    // s[l, r]下标从1开始
    long long query(int l, int r) {
        return (H[r] - H[l - 1] * P[r - l + 1] % MOD + MOD) % MOD;
    }
};

// 双模数
int MOD1 = 998244353 + rnd(0, 1e9), BASE1 = 233 + rnd(0, 1e3);
int MOD2 = 998244353 + rnd(0, 1e9), BASE2 = 233 + rnd(0, 1e3);
struct DoubleHash {
    StringHash hash1, hash2;

    DoubleHash(string &s) {
        hash1 = StringHash(s, MOD1, BASE1);
        hash2 = StringHash(s, MOD2, BASE2);
    }

    pair<long long, long long> query(int l, int r) {
        return make_pair(hash1.query(l, r), hash2.query(l, r));
    }
};

class Solution {
public:
    vector<bool> findAnswer(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> g(n);
        for (int i = 1; i < n; i++) {
            int p = parent[i];
            g[p].push_back(i);
        }

        string dfs_str = "";
        vector<int> in(n), out(n);
        int time = 0;
        auto dfs = [&](auto &&self, int x) -> void {
            in[x] = time;
            for (int y : g[x]) {
                self(self, y);
            }
            time++;
            dfs_str.push_back(s[x]);
            out[x] = time;
        };
        dfs(dfs, 0);

        StringHash sh1(dfs_str);
        reverse(dfs_str.begin(), dfs_str.end());
        StringHash sh2(dfs_str);

        vector<bool> ans(n, false);
        for (int i = 0; i < n; i++) {
            int l = in[i], r = out[i] - 1;
            // 正序 [l, r]
            i64 h1 = sh1.query(l + 1, r + 1);
            // 逆序 [n - 1 - r, n - 1 - l]
            i64 h2 = sh2.query(n - r, n - l);
            if (h1 == h2) ans[i] = true;
        }
        return ans;
    }
};