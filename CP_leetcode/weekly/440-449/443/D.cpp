/*************************************************************************
    > File Name: D.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-03-31 00:37
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

template<typename T, typename Compare = less<T>>
class LazyHeap {
    priority_queue<T, vector<T>, Compare> pq;
    unordered_map<T, int> remove_cnt; // 每个元素剩余需要删除的次数
    size_t sz = 0; // 实际大小
    long long s = 0; // 堆中元素总和

    // 正式执行删除操作
    void apply_remove() {
        while (!pq.empty() && remove_cnt[pq.top()] > 0) {
            remove_cnt[pq.top()]--;
            pq.pop();
        }
    }

public:
    size_t size() {
        return sz;
    }

    long long sum() {
        return s;
    }

    // 删除
    void remove(T x) {
        remove_cnt[x]++; // 懒删除
        sz--;
        s -= x;
    }

    // 查看堆顶
    T top() {
        apply_remove();
        return pq.top();
    }

    // 出堆
    T pop() {
        apply_remove();
        T x = pq.top();
        pq.pop();
        sz--;
        s -= x;
        return x;
    }

    // 入堆
    void push(T x) {
        if (remove_cnt[x] > 0) {
            remove_cnt[x]--; // 抵消之前的删除
        } else {
            pq.push(x);
        }
        sz++;
        s += x;
    }

    // push(x) 然后 pop()
    T push_pop(T x) {
        apply_remove();
        pq.push(x);
        s += x;
        x = pq.top();
        pq.pop();
        s -= x;
        return x;
    }
};

vector<i64> get_dis(vector<int>& nums, int k) {
    int n = nums.size();
    vector<i64> ans(n - k + 1);
    LazyHeap<int> L;                // 大根堆
    LazyHeap<int, greater<int>> R;  // 小根堆

    for (int i = 0; i < n; i++) {
        int in = nums[i];
        if (L.size() == R.size()) {
            L.push(R.push_pop(in));
        } else {
            R.push(L.push_pop(in));
        }

        if (i < k - 1) continue;
        int l = i - k + 1;

        // 中位数贪心
        i64 v = L.top();
        i64 s1 = v * L.size() - L.sum(); // 左半部分
        i64 s2 = R.sum() - v * R.size(); // 右半部分
        ans[l] = s1 + s2;

        int out = nums[l];
        if (out <= L.top()) {
            L.remove(out);
            if (L.size() < R.size()) {
                L.push(R.pop());
            }
        } else {
            R.remove(out);
            if (L.size() > R.size() + 1) {
                R.push(L.pop());
            }
        }
    }
    return ans;
}

class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n =  nums.size();
        auto dis = get_dis(nums, x);
        V f(k + 1, V<i64>(n + 1));
        for (int i = 1; i <= k; i++) {
            f[i][i * x - 1] = infLL;
            for (int j = i * x; j <= n - (k - i) * x; j++) {
                f[i][j] = min(f[i][j - 1], f[i - 1][j - x] + dis[j - x]);
            }
        }
        return f[k][n];
    }
};