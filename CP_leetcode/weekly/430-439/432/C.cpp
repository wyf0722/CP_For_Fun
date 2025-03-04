/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-01-12 14:22
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

/**
 * https://github.com/the-tourist/algo/blob/master/graph/dijkstra.cpp
*/
template <typename T>
class graph {
   public:
    struct edge {
        int from;
        int to;
        T cost;
    };

    vector<edge> edges;
    vector<vector<int>> g;
    int n;

    graph(int _n) : n(_n) { g.resize(n); }

    virtual int add(int from, int to, T cost) = 0;
};

// 有向图
template <typename T>
class digraph : public graph<T> {
   public:
    using graph<T>::edges;
    using graph<T>::g;
    using graph<T>::n;

    digraph(int _n) : graph<T>(_n) {}

    int add(int from, int to, T cost = 1) {
        assert(0 <= from && from < n && 0 <= to && to < n);
        int id = (int)edges.size();
        g[from].push_back(id);
        edges.push_back({from, to, cost});
        return id;
    }

    digraph<T> reverse() const {
        digraph<T> rev(n);
        for (auto& e : edges) {
            rev.add(e.to, e.from, e.cost);
        }
        return rev;
    }
};

// 无向图
template <typename T>
class undigraph : public graph<T> {
   public:
    using graph<T>::edges;
    using graph<T>::g;
    using graph<T>::n;

    undigraph(int _n) : graph<T>(_n) {}

    int add(int from, int to, T cost = 1) {
        assert(0 <= from && from < n && 0 <= to && to < n);
        int id = (int)edges.size();
        g[from].push_back(id);
        g[to].push_back(id);
        edges.push_back({from, to, cost});
        return id;
    }
};

template <typename T>
vector<T> dijkstra(const graph<T>& g, int start) {
    assert(0 <= start && start < g.n);
    vector<T> dist(g.n, numeric_limits<T>::max());
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> s;
    dist[start] = 0;
    s.emplace(dist[start], start);
    while (!s.empty()) {
        T expected = s.top().first;
        int i = s.top().second;
        s.pop();
        if (dist[i] != expected) {
            continue;
        }
        for (int id : g.g[i]) {
            auto& e = g.edges[id];
            int to = e.from ^ e.to ^ i;
            int nd = max(dist[i], e.cost);
            if (nd < dist[to]) {
                dist[to] = nd;
                s.emplace(dist[to], to);
            }
        }
    }
    return dist;
    // returns numeric_limits<T>::max() if there's no path
}

// 以上模板修正最短路径更新方式
class Solution {
public:
    int minMaxWeight(int n, vector<vector<int>>& edges, int threshold) {
        digraph<int> g(n);
        for (auto &e : edges) {
            g.add(e[1], e[0], e[2]);
        }
        auto dis = dijkstra(g, 0);
        auto mx = ranges::max(dis);
        if (mx == numeric_limits<int>::max()) return -1;
        return mx;
    }
};