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

struct Solver {
    int k;
    // s1小，s2大
    multiset<pii> s1, s2;
    i64 sum;

    Solver(int _k): k(_k) {
        sum = 0;
    }

    void maintain() {
        while (!s1.empty() && s2.size() < k) {
            pii p = *(s1.rbegin());
            s2.insert(p);
            sum += 1LL * p.first * p.second;
            s1.erase(prev(s1.end()));
        }
        while (s2.size() > k) {
            pii p = *(s2.begin());
            s1.insert(p);
            s2.erase(s2.begin());
            sum -= 1LL * p.first * p.second;
        }
    }

    void add(pii p) {
        if (!s1.empty() && p <= *(s1.rbegin())) {
            s1.insert(p);
        } else {
            s2.insert(p);
            sum += 1LL * p.first * p.second;
        }
        maintain();
    }

    void remove(pii p) {
        if (auto it = s2.find(p); it != s2.end()) {
            s2.erase(it);
            sum -= 1LL * p.first * p.second;
        } else {
            s1.erase(s1.find(p));
        }
    }
};

class Solution {
public:
    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        int n = nums.size();
        vector<i64> ans;
        unordered_map<int, int> cnt;
        Solver solver(x);
        for (int i = 0; i < k - 1; i++) {
            cnt[nums[i]]++;
        }
        for (auto &p : cnt) {
            solver.add({p.second, p.first});
        }
        for (int i = k - 1; i < n; i++) {
            // 移入窗口
            if (cnt[nums[i]] > 0) solver.remove({cnt[nums[i]], nums[i]});
            cnt[nums[i]]++;
            solver.add({cnt[nums[i]], nums[i]});

            ans.push_back(solver.sum);

            // 移出窗口
            solver.remove({cnt[nums[i - k + 1]], nums[i - k + 1]});
            cnt[nums[i - k + 1]]--;
            if (cnt[nums[i - k + 1]] > 0) solver.add({cnt[nums[i - k + 1]], nums[i - k + 1]});
        }
        return ans;
    }
};