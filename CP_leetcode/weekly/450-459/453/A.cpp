/*************************************************************************
    > File Name: A.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-06-08 18:06
************************************************************************/
#include <bits/stdc++.h>
using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#define debug(...) cout << '[' << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

class Solution {
public:
    bool canMakeEqual(vector<int>& nums, int k) {
        int r1 = 0, r2 = 0;
        vector<int> v1(nums), v2(nums);
        for (int i = 0; i < nums.size() - 1; i++) {
            if (v1[i] == -1) {
                v1[i + 1] *= -1;
                r1++;
            } 
            if (v2[i] == 1) {
                v2[i + 1] *= -1;
                r2++;
            }
        }
        if (r1 <= k && v1.back() == 1) return true;
        if (r2 <= k && v2.back() == -1) return true;
        return false;
    }
};