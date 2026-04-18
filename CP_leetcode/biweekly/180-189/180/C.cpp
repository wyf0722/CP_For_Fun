/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2026-04-18 15:01
************************************************************************/
#include <bits/stdc++.h>
using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#define debug(...) cout << '[' << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
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
    int minOperations(vector<int>& nums) {
        int ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (i & 1) {
                // not prime
                if (primes.isprime(nums[i])) {
                    ans += nums[i] == 2 ? 2 : 1;
                }
            } else {
                // to prime
                if (!primes.isprime(nums[i])) {
                    int idx = lower_bound(primes.primes.begin(), primes.primes.end(), nums[i]) - primes.primes.begin();
                    ans += primes.primes[idx] - nums[i];
                }
            }
        }
        return ans;
    }
};