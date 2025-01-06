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
constexpr int MOD = 998244353; // 998244353 1000000007
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
// @link: https://github.com/ecnerwala/cp-book/blob/master/src/modnum.hpp

template <typename T> T mod_inv_in_range(T a, T m) {
    // assert(0 <= a && a < m);
    T x = a, y = m;
    // coeff of a in x and y
    T vx = 1, vy = 0;
    while (x) {
        T k = y / x;
        y %= x;
        vy -= k * vx;
        std::swap(x, y);
        std::swap(vx, vy);
    }
    assert(y == 1);
    return vy < 0 ? m + vy : vy;
}

template <typename T> struct extended_gcd_result {
    T gcd;
    T coeff_a, coeff_b;
};
template <typename T> extended_gcd_result<T> extended_gcd(T a, T b) {
    T x = a, y = b;
    // coeff of a and b in x and y
    T ax = 1, ay = 0;
    T bx = 0, by = 1;
    while (x) {
        T k = y / x;
        y %= x;
        ay -= k * ax;
        by -= k * bx;
        std::swap(x, y);
        std::swap(ax, ay);
        std::swap(bx, by);
    }
    return {y, ay, by};
}

template <typename T> T mod_inv(T a, T m) {
    a %= m;
    a = a < 0 ? a + m : a;
    return mod_inv_in_range(a, m);
}

template <int MOD_> struct modnum {
    static constexpr int MOD = MOD_;
    static_assert(MOD_ > 0, "MOD must be positive");

private:
    int v;

public:

    modnum() : v(0) {}
    modnum(int64_t v_) : v(int(v_ % MOD)) { if (v < 0) v += MOD; }
    explicit operator int() const { return v; }
    friend std::ostream& operator << (std::ostream& out, const modnum& n) { return out << int(n); }
    friend std::istream& operator >> (std::istream& in, modnum& n) { int64_t v_; in >> v_; n = modnum(v_); return in; }

    friend bool operator == (const modnum& a, const modnum& b) { return a.v == b.v; }
    friend bool operator != (const modnum& a, const modnum& b) { return a.v != b.v; }

    modnum inv() const {
        modnum res;
        res.v = mod_inv_in_range(v, MOD);
        return res;
    }
    friend modnum inv(const modnum& m) { return m.inv(); }
    modnum neg() const {
        modnum res;
        res.v = v ? MOD-v : 0;
        return res;
    }
    friend modnum neg(const modnum& m) { return m.neg(); }

    modnum operator- () const {
        return neg();
    }
    modnum operator+ () const {
        return modnum(*this);
    }

    modnum& operator ++ () {
        v ++;
        if (v == MOD) v = 0;
        return *this;
    }
    modnum& operator -- () {
        if (v == 0) v = MOD;
        v --;
        return *this;
    }
    modnum& operator += (const modnum& o) {
        v -= MOD-o.v;
        v = (v < 0) ? v + MOD : v;
        return *this;
    }
    modnum& operator -= (const modnum& o) {
        v -= o.v;
        v = (v < 0) ? v + MOD : v;
        return *this;
    }
    modnum& operator *= (const modnum& o) {
        v = int(int64_t(v) * int64_t(o.v) % MOD);
        return *this;
    }
    modnum& operator /= (const modnum& o) {
        return *this *= o.inv();
    }

    friend modnum operator ++ (modnum& a, int) { modnum r = a; ++a; return r; }
    friend modnum operator -- (modnum& a, int) { modnum r = a; --a; return r; }
    friend modnum operator + (const modnum& a, const modnum& b) { return modnum(a) += b; }
    friend modnum operator - (const modnum& a, const modnum& b) { return modnum(a) -= b; }
    friend modnum operator * (const modnum& a, const modnum& b) { return modnum(a) *= b; }
    friend modnum operator / (const modnum& a, const modnum& b) { return modnum(a) /= b; }
};

template <typename T> T pow(T a, long long b) {
    assert(b >= 0);
    T r = 1; while (b) { if (b & 1) r *= a; b >>= 1; a *= a; } return r;
}

template <typename U, typename V> struct pairnum {
    U u;
    V v;

    pairnum() : u(0), v(0) {}
    pairnum(long long val) : u(val), v(val) {}
    pairnum(const U& u_, const V& v_) : u(u_), v(v_) {}

    friend std::ostream& operator << (std::ostream& out, const pairnum& n) { return out << '(' << n.u << ',' << ' ' << n.v << ')'; }
    friend std::istream& operator >> (std::istream& in, pairnum& n) { long long val; in >> val; n = pairnum(val); return in; }

    friend bool operator == (const pairnum& a, const pairnum& b) { return a.u == b.u && a.v == b.v; }
    friend bool operator != (const pairnum& a, const pairnum& b) { return a.u != b.u || a.v != b.v; }

    pairnum inv() const {
        return pairnum(u.inv(), v.inv());
    }
    pairnum neg() const {
        return pairnum(u.neg(), v.neg());
    }
    pairnum operator- () const {
        return pairnum(-u, -v);
    }
    pairnum operator+ () const {
        return pairnum(+u, +v);
    }

    pairnum& operator ++ () {
        ++u, ++v;
        return *this;
    }
    pairnum& operator -- () {
        --u, --v;
        return *this;
    }

    pairnum& operator += (const pairnum& o) {
        u += o.u;
        v += o.v;
        return *this;
    }
    pairnum& operator -= (const pairnum& o) {
        u -= o.u;
        v -= o.v;
        return *this;
    }
    pairnum& operator *= (const pairnum& o) {
        u *= o.u;
        v *= o.v;
        return *this;
    }
    pairnum& operator /= (const pairnum& o) {
        u /= o.u;
        v /= o.v;
        return *this;
    }

    friend pairnum operator ++ (pairnum& a, int) { pairnum r = a; ++a; return r; }
    friend pairnum operator -- (pairnum& a, int) { pairnum r = a; --a; return r; }
    friend pairnum operator + (const pairnum& a, const pairnum& b) { return pairnum(a) += b; }
    friend pairnum operator - (const pairnum& a, const pairnum& b) { return pairnum(a) -= b; }
    friend pairnum operator * (const pairnum& a, const pairnum& b) { return pairnum(a) *= b; }
    friend pairnum operator / (const pairnum& a, const pairnum& b) { return pairnum(a) /= b; }
};

template <typename tag> struct dynamic_modnum {
private:
#if __cpp_inline_variables >= 201606
    // C++17 and up
    inline static int MOD_ = 0;
    inline static uint64_t BARRETT_M = 0;
#else
    // NB: these must be initialized out of the class by hand:
    //   static int dynamic_modnum<tag>::MOD = 0;
    //   static int dynamic_modnum<tag>::BARRETT_M = 0;
    static int MOD_;
    static uint64_t BARRETT_M;
#endif

public:
    // Make only the const-reference public, to force the use of set_mod
    static constexpr int const& MOD = MOD_;

    // Barret reduction taken from KACTL:
    /**
     * Author: Simon Lindholm
     * Date: 2020-05-30
     * License: CC0
     * Source: https://en.wikipedia.org/wiki/Barrett_reduction
     * Description: Compute $a \% b$ about 5 times faster than usual, where $b$ is constant but not known at compile time.
     * Returns a value congruent to $a \pmod b$ in the range $[0, 2b)$.
     * Status: proven correct, stress-tested
     * Measured as having 4 times lower latency, and 8 times higher throughput, see stress-test.
     * Details:
     * More precisely, it can be proven that the result equals 0 only if $a = 0$,
     * and otherwise lies in $[1, (1 + a/2^64) * b)$.
     */
    static void set_mod(int mod) {
        assert(mod > 0);
        MOD_ = mod;
        BARRETT_M = (uint64_t(-1) / MOD);
    }
    static uint32_t barrett_reduce_partial(uint64_t a) {
        return uint32_t(a - uint64_t((__uint128_t(BARRETT_M) * a) >> 64) * MOD);
    }
    static int barrett_reduce(uint64_t a) {
        int32_t res = int32_t(barrett_reduce_partial(a) - MOD);
        return (res < 0) ? res + MOD : res;
    }

    struct mod_reader {
        friend std::istream& operator >> (std::istream& i, mod_reader) {
            int mod; i >> mod;
            dynamic_modnum::set_mod(mod);
            return i;
        }
    };
    static mod_reader MOD_READER() {
        return mod_reader();
    }

private:
    int v;

public:

    dynamic_modnum() : v(0) {}
    dynamic_modnum(int64_t v_) : v(int(v_ % MOD)) { if (v < 0) v += MOD; }
    explicit operator int() const { return v; }
    friend std::ostream& operator << (std::ostream& out, const dynamic_modnum& n) { return out << int(n); }
    friend std::istream& operator >> (std::istream& in, dynamic_modnum& n) { int64_t v_; in >> v_; n = dynamic_modnum(v_); return in; }

    friend bool operator == (const dynamic_modnum& a, const dynamic_modnum& b) { return a.v == b.v; }
    friend bool operator != (const dynamic_modnum& a, const dynamic_modnum& b) { return a.v != b.v; }

    dynamic_modnum inv() const {
        dynamic_modnum res;
        res.v = mod_inv_in_range(v, MOD);
        return res;
    }
    friend dynamic_modnum inv(const dynamic_modnum& m) { return m.inv(); }
    dynamic_modnum neg() const {
        dynamic_modnum res;
        res.v = v ? MOD-v : 0;
        return res;
    }
    friend dynamic_modnum neg(const dynamic_modnum& m) { return m.neg(); }

    dynamic_modnum operator- () const {
        return neg();
    }
    dynamic_modnum operator+ () const {
        return dynamic_modnum(*this);
    }

    dynamic_modnum& operator ++ () {
        v ++;
        if (v == MOD) v = 0;
        return *this;
    }
    dynamic_modnum& operator -- () {
        if (v == 0) v = MOD;
        v --;
        return *this;
    }
    dynamic_modnum& operator += (const dynamic_modnum& o) {
        v -= MOD-o.v;
        v = (v < 0) ? v + MOD : v;
        return *this;
    }
    dynamic_modnum& operator -= (const dynamic_modnum& o) {
        v -= o.v;
        v = (v < 0) ? v + MOD : v;
        return *this;
    }
    dynamic_modnum& operator *= (const dynamic_modnum& o) {
        v = barrett_reduce(int64_t(v) * int64_t(o.v));
        return *this;
    }
    dynamic_modnum& operator /= (const dynamic_modnum& o) {
        return *this *= o.inv();
    }

    friend dynamic_modnum operator ++ (dynamic_modnum& a, int) { dynamic_modnum r = a; ++a; return r; }
    friend dynamic_modnum operator -- (dynamic_modnum& a, int) { dynamic_modnum r = a; --a; return r; }
    friend dynamic_modnum operator + (const dynamic_modnum& a, const dynamic_modnum& b) { return dynamic_modnum(a) += b; }
    friend dynamic_modnum operator - (const dynamic_modnum& a, const dynamic_modnum& b) { return dynamic_modnum(a) -= b; }
    friend dynamic_modnum operator * (const dynamic_modnum& a, const dynamic_modnum& b) { return dynamic_modnum(a) *= b; }
    friend dynamic_modnum operator / (const dynamic_modnum& a, const dynamic_modnum& b) { return dynamic_modnum(a) /= b; }
};

template <typename T> struct mod_constraint {
    T v, mod;

    friend mod_constraint operator & (mod_constraint a, mod_constraint b) {
        if (a.mod < b.mod) std::swap(a, b);
        if (b.mod == 1) return a;

        extended_gcd_result<T> egcd = extended_gcd<T>(a.mod, b.mod);
        assert(a.v % egcd.gcd == b.v % egcd.gcd);

        T extra = b.v - a.v % b.mod;
        extra /= egcd.gcd;

        extra *= egcd.coeff_a;
        extra %= b.mod / egcd.gcd;
        extra += (extra < 0) ? b.mod / egcd.gcd : 0;

        return mod_constraint{
            a.v + extra * a.mod,
            a.mod * (b.mod / egcd.gcd)
        };
    }
};

using Z = modnum<1'000'000'007>;

void solve() {
    string s;
    cin >> s;
    int k;
    cin >> k;

    if (k == 0) {
        cout << 1 << endl;
    } else if (k == 1) {
        cout << s.size() - 1 << endl;
    } else {
        // f*(x) = f*(f(x)) + 1 = k - 1
        // f*(f(x)) = k
        // 多少个x恰有k
        int n = s.size();
        vector<vector<Z>> mem(n, vector<Z>(n + 1, -1));
        auto dp = [&](auto &&self, int i, int c, bool is_limit) -> Z {
            if (c == 0) {
                return 1;
            }
            if (i == n) {
                return 0;
            }
            if (!is_limit) {
                if (mem[i][c] != -1) {
                    return mem[i][c];
                }
            }
            int up = is_limit ? (s[i] - '0') : 1;
            Z res = 0;
            for (int d = 0; d <= up; d++) {
                res += self(self, i + 1, c - d, up == d && is_limit);
            }
            if (!is_limit) mem[i][c] = res;
            return res;
        };

        Z ans = 0;
        vector<Z> f(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            f[i] = f[__builtin_popcount(i)] + 1;
            if (f[i] == k) {
                ans += dp(dp, 0, i, true);
            }
        }
        cout << ans << endl;
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