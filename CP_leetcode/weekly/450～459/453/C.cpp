/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-06-08 21:37
************************************************************************/
#include <bits/stdc++.h>

using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#define debug(...) cout << '[' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

using i64 = long long;
const int inf = INT_MAX / 2 - 100;
const i64 infLL = LLONG_MAX / 3;
constexpr int MOD = 1000000007; // 998244353 1000000007
int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};
template <class T> using V = vector<T>;
template<typename T> using min_heap=priority_queue<T,vector<T>,greater<T>>;
template<typename T> using max_heap=priority_queue<T>;

constexpr int popcount(int x) { return __builtin_popcount(x); }
constexpr int topbit(int x) { return x == 0 ? 0 : 31 - __builtin_clz(x); }

template <class T> bool chmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }  // set a = min(a,b)
template <class T> bool chmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }  // set a = max(a,b)

template<class T, class U> T fstTrue(T lo, T hi, U f) { ++hi; assert(lo <= hi); while (lo < hi) { T mid = lo + (hi - lo) / 2; f(mid) ? hi = mid : lo = mid + 1; } return lo; }
template<class T, class U> T lstTrue(T lo, T hi, U f) { --lo; assert(lo <= hi); while (lo < hi) { T mid = lo + (hi - lo + 1) / 2; f(mid) ? lo = mid : hi = mid - 1; } return lo; }

/**
 * https://github.com/the-tourist/algo/blob/master/data/sparsetable.cpp
 */
template <typename T, typename F>
class SparseTable {
   public:
    int n;
    vector<vector<T>> mat;
    F func;

    SparseTable(const vector<T>& a, const F& f) : func(f) {
        n = static_cast<int>(a.size());
        int max_log = 32 - __builtin_clz(n);
        mat.resize(max_log);
        mat[0] = a;
        for (int j = 1; j < max_log; j++) {
            mat[j].resize(n - (1 << j) + 1);
            for (int i = 0; i <= n - (1 << j); i++) {
                mat[j][i] = func(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    T query(int from, int to) const {
        assert(0 <= from && from <= to && to <= n - 1);
        int lg = 32 - __builtin_clz(to - from + 1) - 1;
        return func(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
    }
};

auto get_max = [](auto a, auto b) { return max(a, b); };

auto get_min = [](auto a, auto b) { return min(a, b); };

// SparseTable<int, decltype(get_max)> st(input_data, get_max);

template<class Info>
struct SegmentTree {
    int n;
    std::vector<Info> info;
    SegmentTree() : n(0) {}
    SegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    SegmentTree(std::vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(std::vector(n_, v_));
    }
    template<class T>
    void init(std::vector<T> init_) {
        n = init_.size();
        info.assign(4 << std::__lg(n), Info());
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
    template<class F>
    int findFirst(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findFirst(int l, int r, F pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
    template<class F>
    int findLast(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findLast(int l, int r, F pred) {
        return findLast(1, 0, n, l, r, pred);
    }
};

/**
 * Hints:
 *      1. don't forget to set default value (T variable = value)
 *      2. use Info or const Info& in operator+
 */
struct Info {
    int x = 0;
};

// use Info or const Info &
Info operator+(const Info &a, const Info &b) {
    return Info{(a.x + b.x) % MOD};
}

// class Solution {
// public:
//     int countPartitions(vector<int>& nums, int k) {
//         int n = nums.size();
//         SparseTable<int, decltype(get_min)> st_mn(nums, get_min);
//         SparseTable<int, decltype(get_max)> st_mx(nums, get_max);
//         vector<int> dp(n + 1);
//         dp[0] = 1;
//         SegmentTree<Info> seg(n + 1);
//         seg.modify(0, Info{1});
//         for (int i = 0, j = 0; i < n; i++) {
//             while (st_mx.query(j, i) - st_mn.query(j, i) > k) {
//                 j++;
//             }
//             // 左端点 [j, i] 均合法
//             // for (int l = j; l <= i; l++) {
//             //     dp[i + 1] += dp[l];
//             //     dp[i + 1] %= MOD;
//             // }
//             int delta = seg.rangeQuery(j, i + 1).x;
//             dp[i + 1] += delta;
//             dp[i + 1] %= MOD;
//             seg.modify(i + 1, Info{dp[i + 1]});
//         }
//         return dp[n];
//     }
// };

void add_mod(int &x, int y) {
    x = (x + y) % MOD;
    if (x < 0) x += MOD;
}
class Solution {
public:
    int countPartitions(vector<int>& nums, int k) {
        int n = nums.size();
        SparseTable<int, decltype(get_min)> st_mn(nums, get_min);
        SparseTable<int, decltype(get_max)> st_mx(nums, get_max);
        vector<int> dp(n + 1);
        dp[0] = 1;
        vector<int> dp_s(n + 1);
        dp_s[0] = 1;
        for (int i = 0, j = 0; i < n; i++) {
            while (st_mx.query(j, i) - st_mn.query(j, i) > k) {
                j++;
            }
            // 左端点 [j, i] 均合法
            // for (int l = j; l <= i; l++) {
            //     dp[i + 1] += dp[l];
            //     dp[i + 1] %= MOD;
            // }
            add_mod(dp[i + 1], dp_s[i] - (j ? dp_s[j - 1] : 0));
            add_mod(dp_s[i + 1], dp_s[i] + dp[i + 1]);
        }
        return dp[n];
    }
};