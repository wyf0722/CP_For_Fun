/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-02-16 19:37
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

class Solution {
public:
    bool maxSubstringLength(string s, int k) {
        int n = s.size();
        vector<vector<int>> pos(26);
        vector<vector<int>> pre(n + 1, vector<int>(26));
        for (int i = 0; i < n; i++) {
            pos[s[i] - 'a'].push_back(i);
            pre[i + 1][s[i] - 'a']++;
            for (int j = 0; j < 26; j++) {
                pre[i + 1][j] += pre[i][j];
            }
        }

        vector<vector<int>> segs;
        for (int ch = 0; ch < 26; ch++) {
            if (pos[ch].empty()) {
                continue;
            }
            int l = pos[ch][0], r = pos[ch].back();
            while (1) {
                bool ok = true;
                for (int i = 0; i < 26; i++) {
                    int cnt_i = pre[r + 1][i] - pre[l][i];
                    if (cnt_i > 0 && cnt_i < pos[i].size()) {
                        ok = false;
                        l = min(l, pos[i][0]);
                        r = max(r, pos[i].back());
                    }
                }
                if (ok) break;
            }
            if (!(l == 0 && r == n - 1)) {
                segs.push_back({l, r});
            }
        }
        sort(segs.begin(), segs.end(), [&](auto &e1, auto &e2) {
            return e1[1] < e2[1];
        });
        int R = -1;
        int cnt = 0;
        for (auto &seg : segs) {
            int l = seg[0], r = seg[1];
            if (l > R) {
                R = r;
                cnt++;
            }
        }
        return cnt >= k;
    }
};