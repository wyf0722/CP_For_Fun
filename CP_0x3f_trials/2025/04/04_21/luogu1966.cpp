/*************************************************************************
    > File Name: P_1966_NOIP_2013_提高组_火柴排队.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-04-23 12:47
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

#define MULTICASE 0
// 求逆序对
i64 count(vector<int> &v, int l, int r) {
    if (l >= r) return 0;
    int mid = (l + r) / 2;
    i64 left = count(v, l, mid);
    i64 right = count(v, mid + 1, r);
    i64 res = left + right;
    int i = l, j = mid + 1;
    vector<int> tmp(r - l + 1);
    for (int idx = 0; idx < r - l + 1; idx++) {
        if (i <= mid && (j > r || v[i] <= v[j])) {
            res += j - mid - 1;
            tmp[idx] = v[i++];
        } else {
            tmp[idx] = v[j++];
        }
    }
    for (int i = 0; i < r - l + 1; i++) {
        v[l + i] = tmp[i];
    }
    return res;
}
void solve() {
    int n;
    cin >> n;
    // 相对大小
    auto f = [&]() -> vector<int> {
        vector<int> v(n);
        for (int i = 0; i < n; ++i) {
            cin >> v[i];
        }
        vector<int> ids(n);
        iota(ids.begin(), ids.end(), 0);
        sort(ids.begin(), ids.end(), [&](int x, int y) { return v[x] < v[y]; });
        for (int i = 0; i < n; i++) {
            v[ids[i]] = i;
        }
        return v;
    };
    auto a = f(), b = f();
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        p[a[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        b[i] = p[b[i]];
    }
    cout << count(b, 0, n - 1) % (int)(1e8 - 3) << '\n';
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