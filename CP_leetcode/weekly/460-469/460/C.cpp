/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-08-02 23:31
************************************************************************/
#include <bits/stdc++.h>
#include <queue>
#include <unordered_map>
#include <vector>

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
const int MX = 1e6 + 10;
struct Primes {
    vector<int> lpf, lpfcnt, primes, remaining;

    Primes(int n) {
        lpf.resize(n + 1);
        lpfcnt.resize(n + 1);
        remaining.resize(n + 1);
        for (int i = 2; i <= n; i++) {
            if (!lpf[i]) {
                lpf[i] = i;
                lpfcnt[i] = remaining[i] = 1;
                primes.push_back(i);
            }
            for (int j = 0; i * primes[j] <= n; j++) {
                int val = i * primes[j];
                lpf[val] = primes[j];
                lpfcnt[val] = lpfcnt[primes[j]] + (lpf[i] == primes[j] ? lpfcnt[i] : 0);
                remaining[val] = (lpf[i] == primes[j]) ? remaining[i] : i;
                if (primes[j] == lpf[i])
                    break;
            }
        }
    }

    bool isprime(long long x) {
        if (x < 2)
            return false;
        if (x < lpf.size())
            return lpf[x] == x;
        for (long long i = 2; i * i <= x; i++) {
            if (!(x % i))
                return false;
        }
        return true;
    }

    vector<pair<int, int>> factorise(int x) {
        vector<pair<int, int>> factors;
        for (; x > 1; x = remaining[x])
            factors.emplace_back(lpf[x], lpfcnt[x]);
        return factors;
    }
} primes(MX);

class Solution {
public:
    int minJumps(vector<int>& nums) {
        int n = nums.size();
        // prime -> pos to move
        unordered_map<int, vector<int>> mp;
        for (int i = 0; i < n; i++) {
            for (auto [p, c] : primes.factorise(nums[i])) {
                mp[p].push_back(i);
            }
        }

        vector<int> dis(n, n);
        dis[0] = 0;
        min_heap<pair<int, int>> h;
        h.emplace(0, 0);
        while (!h.empty()) {
            auto [d, i] = h.top();
            h.pop();
            if (dis[i] != d) continue;
            if (i && dis[i - 1] > d + 1) {
                dis[i - 1] = d + 1;
                h.emplace(d + 1, i - 1);
            }
            if (i + 1 < n && dis[i + 1] > d + 1) {
                dis[i + 1] = d + 1;
                h.emplace(d + 1, i + 1);
            }
            if (mp.count(nums[i])) {
                for (auto &j : mp[nums[i]]) {
                    if (dis[j] > d + 1) {
                        dis[j] = d + 1;
                        h.emplace(d + 1, j);
                    }
                }
                mp.erase(nums[i]);
            }
        }
        return dis[n - 1];
    }
};