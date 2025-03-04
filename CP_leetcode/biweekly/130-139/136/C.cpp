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
int MOD = 1e9 + 7;
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
 * 𝓽𝓱𝓮 𝓼𝓸𝓵𝓾𝓽𝓲𝓸𝓷 𝓸𝓯 𝔀𝔂𝓯0722
 */

class Solution {
public:
    int minFlips(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vvi vis(m, vi(n));

        auto ck = [&](int i, int j) -> bool {
            if (!vis[i][j]) {
                vis[i][j] = 1;
                return false;
            }
            return true;
        };
        int ans = 0;
        int c1 = 0, c21 = 0, c22 = 0;
        for (int i = 0; i < (m + 1) / 2; i++) {
            for (int j = 0; j < (n + 1) / 2; j++) {
                vi c(2);
                if (!ck(i, j)) {
                    c[grid[i][j]]++;
                }
                if (!ck(i, n - 1 - j)) {
                    c[grid[i][n - 1 - j]]++;
                }
                if (!ck(m - 1 - i, j)) {
                    c[grid[m - 1 - i][j]]++;
                }
                if (!ck(m - 1 - i, n - 1 - j)) {
                    c[grid[m - 1 - i][n - 1 - j]]++;
                }
                if (c[1] + c[0] == 4) {
                    if (c[1] % 4 == 0) continue;
                    if (c[1] == 3) {
                        ans += 1;
                    }
                    if (c[1] == 2) {
                        ans += 2;
                    }
                    if (c[1] == 1) {
                        ans += 1;
                    }
                } else if (c[1] + c[0] == 2) {
                    if (c[1] == 0) continue;
                    if (c[1] == 2) {
                        c22 += 1;
                    }
                    if (c[1] == 1) {
                        c21 += 1;
                    }
                } else {
                    if (c[1]) c1 += 1;
                }
            }
        }
        ans += c21;
        if ((c22 + c21) % 2) {
            if (c21 == 0) ans += 2;
        }
        return ans + c1;
    }
};