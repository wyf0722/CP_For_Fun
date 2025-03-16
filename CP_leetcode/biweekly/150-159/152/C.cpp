/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-03-16 14:28
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

struct Node {
    int cnt;
    vector<Node*> sons;
    Node() {
        cnt = 0;
        sons.resize(26);
    }
};

struct Trie {
    Node* root;

    Trie() {
        root = new Node();
    }

    int add(string word, int k) {
        auto cur = root;
        cur->cnt++;
        int d = 0, res = 0;
        for (auto &ch : word) {
            int nxt = ch - 'a';
            if (cur->sons[nxt] == nullptr) {
                cur->sons[nxt] = new Node();
            }
            cur = cur->sons[nxt];
            cur->cnt++;
            d++;
            if (cur->cnt >= k) {
                res = d;
            }
        }
        return res;
    }

    void remove(string word) {
        auto cur = root;
        cur->cnt--;
        for (auto &ch : word) {
            int nxt = ch - 'a';
            cur = cur->sons[nxt];
            cur->cnt--;
        }
    }

    // int get(int k) {
    //     int res = -1;
    //     queue<Node*> q;
    //     q.emplace(root);
    //     while (!q.empty()) {
    //         int sz = q.size();
    //         while (sz--) {
    //             auto cur = q.front();
    //             q.pop();
    //             for (auto &son : cur->sons) {
    //                 if (son && son->cnt >= k) {
    //                     q.emplace(son);
    //                 }
    //             }
    //         }
    //         res++;
    //     }
    //     return res;
    // }
    int get(Node* cur, int k) {
        int ans = 0;
        for (auto &son : cur->sons) {
            if (son == nullptr) continue;
            if (son->cnt >= k) {
                int res = get(son, k) + 1;
                ans = max(ans, res);
            }
        }
        return ans;
    }
};


class Solution {
public:
    vector<int> longestCommonPrefix(vector<string>& words, int k) {
        Trie tr;
        int mx = 0, idx = -1;
        int n = words.size();
        for (int i = 0; i < n; i++) {
            string word = words[i];
            int r = tr.add(word, k);
            if (r > mx) {
                mx = r;
                idx = i;
            }
        }
        if (mx == 0) return vector<int>(n);

        string target = words[idx].substr(0, mx);
        tr.remove(target);
        int mx2 = tr.get(tr.root, k);
        vector<int> ans;
        for (auto &w : words) {
            if (w.size() >= target.size() && w.find(target) == 0) {
                ans.push_back(mx2);
            } else {
                ans.push_back(mx);
            }
        }
        return ans;
    }
};