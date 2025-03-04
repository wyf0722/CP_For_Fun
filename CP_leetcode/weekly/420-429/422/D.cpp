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

/*************************************************************************
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
************************************************************************/
const int MX = 41;
vector<i64> f;
vector<i64> inv_f;

i64 qpow(i64 x, int y) {
    i64 res = 1;
    for (; y; y /= 2) {
        if (y & 1) {
            res = res * x % MOD;
        }
        x = x * x % MOD;
    }
    return res;
}

auto init = []() {
    f.resize(MX);
    inv_f.resize(MX);
    f[0] = 1;
    for (int i = 1; i < MX; i++) {
        f[i] = f[i - 1] * i % MOD;
    }
    inv_f[MX - 1] = qpow(f[MX - 1], MOD - 2);
    for (int i = MX - 1; i > 0; i--) {
        inv_f[i - 1] = inv_f[i] * i % MOD;
    }
    return 0;
}();

class Solution {
public:
    int countBalancedPermutations(string num) {
        int cnt[10];
        int total = 0;
        for (char c : num) {
            cnt[c - '0']++;
            total += c - '0';
        }
        if (total & 1) return 0;

        for (int i = 1; i < 10; i++) cnt[i] += cnt[i - 1];

        int n = num.size(), n1 = n / 2;
        vector<vector<vector<int>>> mem(10, vector<vector<int>>(n1 + 1, vector<int>(total / 2 + 1, -1)));
        auto dfs = [&](auto &&self, int i, int left1, int lefts) -> int {
            if (i < 0) return lefts == 0;
            int &res = mem[i][left1][lefts];
            if (res != -1) return res;
            res = 0;
            int c = cnt[i] - (i ? cnt[i - 1] : 0);
            int left2 = cnt[i] - left1;
            for (int k = max(c - left2, 0); k <= min(c, left1) && k * i <= lefts; k++) {
                int r = self(self, i - 1, left1 - k, lefts - k * i);
                res = (res + r * inv_f[k] % MOD * inv_f[c - k] % MOD) % MOD;
            }
            return res;
        };
        return f[n1] * f[n - n1] % MOD * dfs(dfs, 9, n1, total / 2) % MOD;
    }
};