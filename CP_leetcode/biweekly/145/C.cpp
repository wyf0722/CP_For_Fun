/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2024-12-08 00:32
************************************************************************/
#include <bits/stdc++.h>
using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#define debug(...) cout << '[' << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

using i64 = long long;

// https://github.com/Joshc88/CPTemplates/blob/main/Math/primes.h
const int MX = 1e5 + 10;
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
    int minOperations(int n, int m) {
        if (primes.isprime(n) || primes.isprime(m)) return -1;
        vector<int> dis(10000, -1);
        dis[n] = n;
        queue<int> q;
        q.push(n);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            string sx = to_string(x);
            int sz = sx.size();
            for (int i = 0; i < sz; i++) {
                if (sx[i] != '9') {
                    sx[i] += 1;
                    int y = stoi(sx);
                    if (!primes.isprime(y) && (dis[y] == -1 || dis[y] > dis[x] + y)) {
                        dis[y] = dis[x] + y;
                        q.push(y);
                    }
                    sx[i] -= 1;
                }
                if (sx[i] != '0') {
                    sx[i] -= 1;
                    int y = stoi(sx);
                    if (!primes.isprime(y) && (dis[y] == -1 || dis[y] > dis[x] + y)) {
                        dis[y] = dis[x] + y;
                        q.push(y);
                    }
                    sx[i] += 1;
                }
            }
        }
        return dis[m];
    }
};