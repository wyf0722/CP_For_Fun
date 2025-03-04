/*************************************************************************
    > File Name: D.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-02-16 00:36
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
constexpr int MOD = 998244353; // 998244353 1000000007
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

    StringHash(const string &s, int m = SINGLE_MOD, int b = SINGLE_BASE) {
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

    DoubleHash(const string &s) {
        hash1 = StringHash(s, MOD1, BASE1);
        hash2 = StringHash(s, MOD2, BASE2);
    }

    pair<long long, long long> query(int l, int r) {
        return make_pair(hash1.query(l, r), hash2.query(l, r));
    }
};

class Solution {
public:
    int shortestMatchingSubstring(string s, string p) {
        int n = s.size(), m = p.size();

        vector<int> ps;
        for (int i = 0; i < m; i++) {
            if (p[i] == '*') {
                ps.push_back(i);
            }
        }

        StringHash s_hash(s);
        // 找到 str 在 s 中的位置
        auto f = [&](string str) -> set<int> {
            int len = str.size();
            StringHash hash(str);
            i64 val = hash.query(1, len);
            set<int> res;
            for (int i = 1; i + len - 1 <= n; i++) {
                if (len == 0 || s_hash.query(i, i + len - 1) == val) {
                    res.insert(i);
                }
            }
            return res;
        };

        int l_len = ps[0];
        int r_len = m - 1 - ps[1];
        set<int> ls = f(p.substr(0, l_len));
        set<int> rs = f(p.substr(ps[1] + 1, r_len));

        int ans = inf;
        int m_len = ps[1] - ps[0] - 1;
        StringHash hash(p.substr(ps[0] + 1, m_len));
        i64 val = hash.query(1, m_len);
        for (int i = 1; i + m_len - 1 <= n; i++) {
            // 找到匹配中间的位置
            if (m_len != 0 && s_hash.query(i, i + m_len - 1) != val) {
                continue;
            }
            // 找到左边第一个小于自己的
            auto l_it = ls.upper_bound(i - l_len);
            if (l_it == ls.begin()) {
                continue;
            }
            int l = *prev(l_it);
            // 找到右边第一个大于自己的
            auto r_it = rs.lower_bound(i + m_len);
            if (r_it == rs.end()) {
                continue;
            }
            auto r = *r_it + r_len - 1;
            ans = min(ans, r - l + 1);
        }
        return ans == inf ? -1 : ans;
    }
};