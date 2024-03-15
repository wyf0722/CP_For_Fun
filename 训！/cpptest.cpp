#include <bits/stdc++.h>

using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
 
void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#define debug(...) cout << '[' << __FILE__ << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

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
const long long MOD = 1e9 + 7;
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

template <class T>
vector<int> sortidx(const vector<T>& a) {
    int n = a.size();
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j) { return a[i] < a[j]; });
    return idx;
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

template <class T>
vector<T> getPresum(const vector<T>& a) {
    vector<T> s(a.size() + 1);
    rep(i, 0, a.size()) s[i + 1] = s[i] + a[i];
    return s;
}
vector<i64> getPresum(const vector<int>& a) {
    vector<i64> s(a.size() + 1);
    rep(i, 0, a.size()) s[i + 1] = s[i] + a[i];
    return s;
}

template <class T>
bool chmin(T& a, const T& b) {
    return b < a ? a = b, 1 : 0;
}  // set a = min(a,b)
template <class T>
bool chmax(T& a, const T& b) {
    return a < b ? a = b, 1 : 0;
}  // set a = max(a,b)

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

template <typename T>
struct Discrete {
    Discrete() {}
    void add(T t) { p.push_back(t); }

    void init() {
        sort(p.begin(), p.end());
        p.resize(unique(p.begin(), p.end()) - p.begin());
    }

    int size() { return p.size(); }

    int query(T t) { return lower_bound(p.begin(), p.end(), t) - p.begin(); }

    T operator[](int id) { return p[id]; }

    vector<T>& get() { return p; }
    vector<T> p;
};
template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;
    
    Fenwick(int n = 0) {
        init(n);
    }
    
    void init(int n) {
        this->n = n;
        a.assign(n, T());
    }
    
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    
    T sum(int x) {
        auto ans = T();
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }
    
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
    
    int kth(T k) {
        int x = 0;
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && k >= a[x + i - 1]) {
                x += i;
                k -= a[x - 1];
            }
        }
        return x;
    }
};
struct Info {
    int x;
    Info(int x_ = 0): x(x_) {}
    Info& operator+=(const Info &info) {
        this->x = max(this->x, info.x);
        return *this;
    }
};
class Solution {
public:
    vector<int> maximumSumQueries(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        int n = nums1.size();
        vi idx(n);
        iota(all(idx), 0);
        sort(all(idx), [&](auto &a, auto &b) {
            return nums1[a] > nums1[b];
        });

        // 离散化
        Discrete<int> dc;
        for (int x: nums2) dc.add(x);
        for (auto &q: queries) dc.add(q[1]);
        dc.init();

        vvi qs;
        rep(i, 0, queries.size()) {
            qs.push_back({queries[i][0], queries[i][1], i});
        }
        sort(all(qs), [&](auto &a, auto &b) {
            return a[0] > b[0];
        });

        Fenwick<Info> fen(dc.size());
        vi ans(qs.size(), -1);
        int now = 0;
        for (auto q: qs) {
            int x = q[0], y = q[1], id = q[2];
            while (now < n and nums1[idx[now]] >= x) {
                fen.add(dc.size() - 1 - dc.query(nums2[idx[now]]), nums1[idx[now]] + nums2[idx[now]]);
                now++;
            }
            auto info = fen.sum(dc.size() - dc.query(y));
            if (info.x != 0) {
                ans[id] = info.x;
            }
        }
        return ans;
    }
};