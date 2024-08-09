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
    vector<int> timeTaken(vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        vvi g(n);
        for (auto &e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        // t[i]标记完i后，需要t[i]才能标记完子树
        vi t(n);
        auto dfs1 = [&](auto &&self, int x, int fa) -> int {
            t[x] = 0;
            for (int y : g[x]) {
                if (y == fa) continue;
                int cur_t = self(self, y, x) + (y & 1 ? 1 : 2);
                chmax(t[x], cur_t);
            }
            return t[x];
        };
        dfs1(dfs1, 0, -1);

        vi ans(n);
        // fa_t 向上的联通块多久能标记完
        auto dfs2 = [&](auto &&self, int x, int fa, int fa_t) -> void {
            ans[x] = max(fa_t, t[x]);
            // 向下标记每个儿子所在子树的时间，找到最大和次大
            int mx1 = -1, fn1 = -1, mx2 = -1, fn2 = -1;
            for (int y : g[x]) {
                if (y == fa) continue;
                int cur_t = t[y] + (y & 1 ? 1 : 2);
                if (cur_t > mx1) {
                    mx2 = mx1;
                    fn2 = fn1;
                    mx1 = cur_t;
                    fn1 = y;
                } else if (cur_t > mx2) {
                    mx2 = cur_t;
                    fn2 = cur_t;
                }
            }
            for (int y : g[x]) {
                int cur_t = 0;
                if (y == fa) continue;
                if (y == fn1) cur_t = max(fa_t, mx2);
                else cur_t = max(fa_t, mx1);
                self(self, y, x, cur_t + (x & 1 ? 1 : 2));
            }
        };
        dfs2(dfs2, 0, -1, 0);

        return ans;
    }
};