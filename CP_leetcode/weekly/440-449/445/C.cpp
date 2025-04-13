/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-04-13 12:49
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
    string smallestPalindrome(string s, int k) {
        int n = s.size(), m = n / 2;
        // 只用考虑左半部分，如果长度为奇数，中间的字符可以确定
        vector<int> cnt(26, 0);
        for (int i = 0; i < m; i++) {
            cnt[s[i] - 'a']++;
        }
        // 计算组合数
        auto C = [&](int n, int m) -> int {
            m = min(m, n - m); // 注意不加此代码， C(2, 2)过程中会出现res为2的情况
            i64 res = 1;
            for (int i = 1; i <= m; i++) {
                res = res * (n + 1 - i) / i;
                if (res >= k) { // 太大了
                    return k;
                }
            }
            return res;
        };

        // 计算排列数
        auto calc_perm = [&](int x) -> int {
            i64 res = 1;
            for (int c : cnt) {
                if (c == 0) continue;
                // 从x中选c个
                res *= C(x, c);
                if (res >= k) {
                    return k;
                }
                x -= c;
            }
            return res;
        };

        if (calc_perm(m) < k) {
            return "";
        }
        string L(m, '?');
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < 26; j++) {
                if (cnt[j] == 0) continue;
                cnt[j]--;
                int total = calc_perm(m - 1 - i);
                if (total >= k) {
                    L[i] = 'a' + j;
                    break;
                }
                k -= total;
                cnt[j]++;
            }
        }
        string R(L);
        reverse(R.begin(), R.end());
        if (n & 1) {
            L += s[m];
        }
        return L + R;
    }
};