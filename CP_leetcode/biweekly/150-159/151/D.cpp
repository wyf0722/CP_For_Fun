/*************************************************************************
    > File Name: D.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-04-05 23:02
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

// n为奇数  1 0 1 0 1 -> (n / 2)! * ((n + 1) / 2)!
// n为偶数  1010/0101 -> 2 * (n / 2)! * (n / 2)!
vector<i64> f{1};
int init = []() -> int {
    for (int i = 1; f.back() < 1e15; i++) {
        f.push_back(f.back() * i);
        f.push_back(f.back() * i);
    }
    return 0;
}();
class Solution {
public:
    vector<int> permute(int n, long long k) {
        // 按位填写
        k--;
        if (n < f.size() && k >= f[n] * (2 - n % 2)) {
            return {};
        }

        // cand 表示剩余未填的数
        vector<int> cand[2];
        for (int i = 2; i <= n; i += 2)  {
            cand[0].push_back(i);
        }
        for (int i = 1; i <= n; i += 2)  {
            cand[1].push_back(i);
        }

        vector<int> ans(n);
        // 当前填入数字的奇偶性
        int parity = 1;
        for (int i = 0; i < n; i++) {
            int j = 0;
            if (n - 1 - i < f.size()) {
                // 每个组的大小
                i64 sz = f[n - 1 - i];
                j = k / sz;
                k %= sz;
                
                // n为偶数时，第一个数奇偶都可以
                // 1 2 3 4...
                // 1 3 -> j % 2 == 1
                // 2 4 -> j % 2 == 0
                if (n % 2 == 0 && i == 0) {
                    parity = 1 - j % 2;
                    j /= 2;
                }
            }
            ans[i] = cand[parity][j];
            cand[parity].erase(cand[parity].begin() + j);
            parity ^= 1;
        }
        return ans;
    }
};