/*************************************************************************
    > File Name: B.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2026-10-25 00:03
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

// https://github.com/Joshc88/CPTemplates/blob/main/Math/primes.h
const int MX = 1000001;
struct Primes {
    vector<bool> is_prime;
    vector<int> primes;
    vector<i64> p_sum;

    Primes(int n) {
        is_prime.assign(n + 1, true);
        is_prime[0] = is_prime[1] = false;
        for (int i = 2; i <= n; ++i) {
            if (is_prime[i]) {
                primes.push_back(i);
                i64 s = p_sum.empty() ? 0 : p_sum.back();
                p_sum.push_back(s + i);
                if (1LL * i * i <= n) {
                    for (int j = i * i; j <= n; j += i) {
                        is_prime[j] = false;
                    }
                }
            }
        }
    }
} primes(MX);

class Solution {
public:
vector<int> maxPrimes(int n, int s) {
    // bisect_right(primes, n)
    int i = upper_bound(primes.primes.begin(), primes.primes.end(), n) - primes.primes.begin();
    // bisect_right(p_sum, s, 0, i)
    int j = upper_bound(primes.p_sum.begin(), primes.p_sum.begin() + i, (i64)s) - primes.p_sum.begin();
    // primes[:j]
    return vector<int>(primes.primes.begin(), primes.primes.begin() + j);
}
};