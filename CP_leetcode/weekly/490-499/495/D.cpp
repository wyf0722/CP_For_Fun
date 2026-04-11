/*************************************************************************
    > File Name: D.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2026-04-11 20:27
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
#include <vector>
#include <numeric> // 用于 std::iota

struct DSU {
    std::vector<int> f;         // 父节点数组
    std::vector<int> siz;       // 集合大小（按秩合并用）
    std::vector<int> xor_to_parent; // 节点到父节点的异或值（权值）

    DSU() {}
    DSU(int n) {
        init(n);
    }

    // 初始化：n 为节点数
    void init(int n) {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0); // 父节点初始化为自身
        siz.assign(n, 1);                  // 集合大小初始化为 1
        xor_to_parent.assign(n, 0);        // 初始时节点到自身的异或值为 0
    }

    // 带路径压缩的 find，同时更新 xor_to_parent
    int find(int x) {
        if (x != f[x]) {
            int orig_parent = f[x];       // 记录原来的父节点
            f[x] = find(f[x]);            // 递归压缩路径，让 orig_parent 指向根
            xor_to_parent[x] ^= xor_to_parent[orig_parent]; // 更新 x 到根的异或值
        }
        return f[x];
    }

    // 判断 x 和 y 是否连通
    bool same(int x, int y) {
        return find(x) == find(y);
    }

    // 合并 x 和 y，且已知 x 到 y 的异或值为 val
    // 返回值：true 表示成功合并，false 表示已连通
    bool merge(int x, int y, int val) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) {
            return false;
        }
        // 按秩合并：小集合合并到大集合，保持树平衡
        if (siz[rootX] < siz[rootY]) {
            std::swap(rootX, rootY);
            std::swap(x, y);
            // 注意：x 到 y 的异或值 val 无需改变，因为 a^b = b^a
        }
        siz[rootX] += siz[rootY];
        f[rootY] = rootX;
        // 关键：计算 rootY 到 rootX 的异或值
        // 推导：x→rootX 的异或值为 xor_to_parent[x]
        //       y→rootY 的异或值为 xor_to_parent[y]
        //       x→y 的异或值为 val
        // 因此：xor_to_parent[x] ^ xor_to_parent[rootY] ^ xor_to_parent[y] = val
        // 解得：xor_to_parent[rootY] = xor_to_parent[x] ^ xor_to_parent[y] ^ val
        xor_to_parent[rootY] = xor_to_parent[x] ^ xor_to_parent[y] ^ val;
        return true;
    }

    // 获取 x 所在集合的大小
    int size(int x) {
        return siz[find(x)];
    }

    // 获取 x 到 y 的异或值（需保证 x 和 y 已连通）
    int get_xor(int x, int y) {
        find(x); // 确保 x 指向根，xor_to_parent[x] 是 x 到根的异或值
        find(y); // 确保 y 指向根，xor_to_parent[y] 是 y 到根的异或值
        return xor_to_parent[x] ^ xor_to_parent[y];
    }
};

class Solution {
public:
    int numberOfEdgesAdded(int n, vector<vector<int>>& edges) {
        int count = 0;
        DSU dsu(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            if (dsu.same(u, v)) {
                // 核心条件：如果添加边 (u,v,w)，则环的异或值为 get_xor(u,v) XOR w
                // 题目要求环的边权和为偶数，即 (get_xor(u,v) XOR w) == 0
                // 也就是 get_xor(u,v) == w
                if (dsu.get_xor(u, v) == w) {
                    count++;
                }
            } else {
                dsu.merge(u, v, w);
                count++;
            }
        }
        return count;
    }
};