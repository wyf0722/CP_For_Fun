/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2024-12-29 14:25
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
    long long numberOfSubsequences(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int> suf;

        auto gen = [&](int x, int y) -> int {
            int g = gcd(x, y);
            return (x / g) << 16 | (y / g);
        };

        // a * c = b * d
        // a / b = d / c
        for (int i = 4; i < n - 2; i++) {
            int c = nums[i];
            for (int j = i + 2; j < n; j++) {
                int d = nums[j];
                suf[gen(d, c)]++;
            }
        }

        i64 ans = 0;
        for (int i = 2; i < n - 4; i++) {
            int b = nums[i];
            for (int j = 0; j < i - 1; j++) {
                int a = nums[j];
                ans += suf[gen(a, b)];
            }

            int c = nums[i + 2];
            for (int j = i + 4; j < n; j++) {
                int d = nums[j];
                suf[gen(d, c)]--;
            }
        }

        return ans;
    }
};