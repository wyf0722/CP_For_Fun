/*************************************************************************
    > File Name: D_Skibidi_Table.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-04-09 13:49
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

#define MULTICASE 1
// 00 11 -> x 0 0 -> y 0 1
// 10 01      1 1      0 1
void solve() {
    int n, q;
    cin >> n >> q;

    // jiangly solution
    // while (q--) {
    //     string op;
    //     cin >> op;

    //     if (op == "->") {
    //         int x, y;
    //         cin >> x >> y;
    //         x--, y--;

    //         i64 d = 0;
    //         for (int i = 0; i < n; i++) {
    //             int xi = x >> i & 1;
    //             int yi = y >> i & 1;
    //             i64 di = (xi * 2) ^ (yi * 3);
    //             d |= di << (2 * i);
    //         }
    //         cout << d + 1 << '\n';
    //     } else {
    //         i64 d;
    //         cin >> d;
    //         d--;

    //         int x = 0, y = 0;
    //         for (int i = 0; i < n; i++) {
    //             int di = d >> (2 * i) & 3;
    //             int xi = (di & 1) ^ (di >> 1);
    //             int yi = di & 1;
    //             x |= xi << i;
    //             y |= yi << i;
    //         }
    //         cout << x + 1 << ' ' << y + 1 << '\n';
    //     }
    // }

    while (q--) {
        string op;
        cin >> op;

        if (op == "->") {
            i64 x, y;
            cin >> x >> y;
            x--, y--;
            i64 d = 0;
            for (int i = n - 1; i >= 0; i--) {
                // block = len * len = 2^i * 2^i
                i64 len = 1LL << i;
                i64 x1 = x / len, y1 = y / len;
                i64 block_size = 1LL << (2 * i);
                if (x1 == 0 && y1 == 0) {

                } else if (x1 == 0 && y1 == 1) {
                    d += block_size * 3;
                } else if (x1 == 1 && y1 == 0) {
                    d += block_size * 2;
                } else {
                    d += block_size;
                }
                x %= len;
                y %= len;
            }
            cout << d + 1 << '\n';
        } else {
            i64 d;
            cin >> d;
            d--;
            int x = 0, y = 0;
            for (int i = n - 1; i >= 0; i--) {
               i64 len = 1LL << i;
               i64 block_idx = d / (1LL << (2 * i));
               if (block_idx == 0) {

               } else if (block_idx == 1) {
                // 右下
                   x += len;
                   y += len;   
               } else if (block_idx == 2) {
                // 左下
                   x += len; 
               } else {
                // 右上
                   y += len;
               }
               d %= 1LL << (2 * i);
            }
            cout << x + 1 << " " << y + 1 << '\n';
        }
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