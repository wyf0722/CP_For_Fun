/*************************************************************************
    > File Name: D.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2024-12-10 16:55
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

template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;

    Fenwick(int n_ = 0) {
        init(n_);
    }

    void init(int n_) {
        n = n_;
        a.assign(n, T{});
    }

    void add(int x, const T &v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = a[i - 1] + v;
        }
    }

    T sum(int x) {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i - 1];
        }
        return ans;
    }

    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }

    int select(const T &k) {
        int x = 0;
        T cur{};
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};

// don't forget to set default value
// T variable = value
struct Info{
    int x;
    Info(int x_ = 0):x(x_) {}
};
Info operator+(const Info &a, const Info &b) {
    return Info{max(a.x, b.x)};
}

class Solution {
public:
    long long maxRectangleArea(vector<int>& xCoord, vector<int>& yCoord) {
        V<pair<int, int>> points;
        for (int i = 0; i < xCoord.size(); i++) {
            points.emplace_back(xCoord[i], yCoord[i]);
        }
        // 注意：每个矩形的左下角和左上角一定相邻
        sort(points.begin(), points.end());

        sort(yCoord.begin(), yCoord.end());
        yCoord.resize(unique(yCoord.begin(), yCoord.end()) - yCoord.begin());

        auto get_id = [&](int y) -> int {
            return lower_bound(yCoord.begin(), yCoord.end(), y) - yCoord.begin();
        };

        i64 ans = -1;
        Fenwick<int> fen(yCoord.size());
        fen.add(get_id(points[0].second), 1);
        unordered_map<int, tuple<int, int, int>> mp;
        for (int i = 1; i < points.size(); i++) {
            auto &[x1, y1] = points[i - 1];
            auto &[x2, y2] = points[i];
            int id_y2 = get_id(y2);
            fen.add(id_y2, 1);
            if (x1 != x2) continue;

            int cur = fen.rangeSum(get_id(y1), id_y2 + 1);
            auto it = mp.find(y2);
            if (it != mp.end()) {
                auto &[x, y, pre] = it->second;
                if (y == y1 && pre + 2 == cur) {
                    ans = max(ans, 1LL * (x2 - x) * (y2 - y1));
                }
            }
            mp[y2] = {x1, y1, cur};
        }
        return ans;
    }
};