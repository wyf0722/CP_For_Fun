/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-01-12 00:06
************************************************************************/
#include <bits/stdc++.h>
using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#define debug(...) cout << '[' << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

using i64 = long long;

class Solution {
public:
    long long maximumCoins(vector<vector<int>>& coins, int k) {
        auto f = [&]() -> i64 {
            ranges::sort(coins);
            i64 ans = 0, sum = 0;
            int n = coins.size();
            for (int i = 0, j = 0; j < n; j++) {
                sum += 1LL * (coins[j][1] - coins[j][0] + 1) * coins[j][2];
                while (coins[i][1] + k - 1 < coins[j][1]) {
                    sum -= 1LL * (coins[i][1] - coins[i][0] + 1) * coins[i][2];
                    i++;
                }
                i64 remove = max(0LL, 1LL * (coins[j][1] - k + 1 - coins[i][0]) * coins[i][2]);
                ans = max(ans, sum - remove);
            }
            return ans;
        };

        i64 ans1 = f();
        for (auto &coin : coins) {
            coin[0] *= -1;
            coin[1] *= -1;
            swap(coin[0], coin[1]);
        }
        i64 ans2 = f();
        return max(ans1, ans2);
    }
};