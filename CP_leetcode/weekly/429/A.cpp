/*************************************************************************
    > File Name: A.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2024-12-22 12:02
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
    int minimumOperations(vector<int>& nums) {
        vector<int> cnt(101);
        for (int &x : nums) {
            cnt[x]++;
        }
        auto ck = [&]() -> bool {
            for (int x : cnt) if (x > 1) return false;
            return true;
        };
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n;) {
            if (ck()) break;
            ans++;
            cnt[nums[i++]]--;
            if (i < n) cnt[nums[i++]]--;
            if (i < n) cnt[nums[i++]]--;
        }
        return ans;
    }
};