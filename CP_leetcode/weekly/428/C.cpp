/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2024-12-15 14:06
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
    int beautifulSplits(vector<int>& nums) {
        string s = "";
        for (int x : nums) {
            s.push_back(x + 36);
        }
        int n = s.size();
        StringHash hash(s);
        // DoubleHash hash(s);
        int ans = 0;
        for (int len1 = 1; len1 <= n - 2; len1++) {
            for (int len2 = 1; len1 + len2 <= n - 1; len2++) {
                int l1 = 0, r1 = len1 - 1;
                int l2 = len1, r2 = len1 + len2 - 1;
                int l3 = len1 + len2, r3 = n - 1;
                if ((len1 <= len2 && hash.query(l1 + 1, r1 + 1) == hash.query(l2 + 1, l2 + len1)) || \
                (len2 <= n - len1 - len2 && hash.query(l2 + 1, r2 + 1) == hash.query(l3 + 1, l3 + len2))) {
                    ans++;
                }
            }
        }
        return ans;
    }
};