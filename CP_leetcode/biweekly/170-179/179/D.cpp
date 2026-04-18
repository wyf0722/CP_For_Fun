/*************************************************************************
    > File Name: D.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2026-04-18 15:12
************************************************************************/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
constexpr int MOD = 1e9 + 7;
const int MX = 5000;

vector<int> sum(MX + 1);
map<int, vector<int>> digit_sum_2_values;

int init = []() -> int {
    for (int i = 0; i <= MX; i++) {
        int x = i;
        sum[i] = 0;
        while (x) {
            sum[i] += x % 10;
            x /= 10;
        }
        digit_sum_2_values[sum[i]].push_back(i);
    }
    for (auto& p : digit_sum_2_values) {
        sort(p.second.begin(), p.second.end());
    }
    return 0;
}();

class Solution {
public:
    int countArrays(vector<int>& digitSum) {
        // 剪枝：不存在直接返回0
        for (int s : digitSum) {
            if (!digit_sum_2_values.count(s)) return 0;
        }

        // DP 使用 vector<pair<int, int>>，自带有序，无需排序！
        vector<pair<int, int>> dp;
        for (int v : digit_sum_2_values[digitSum[0]]) {
            dp.emplace_back(v, 1);
        }

        for (int i = 1; i < digitSum.size(); i++) {
            vector<pair<int, int>> ndp;
            vector<i64> pre(dp.size() + 1, 0);
            
            // 前缀和（dp已有序，直接计算）
            for (int j = 0; j < dp.size(); j++) {
                pre[j+1] = (pre[j] + dp[j].second) % MOD;
            }

            // 枚举当前合法数字
            for (int cur : digit_sum_2_values[digitSum[i]]) {
                // 二分找 <= cur 的数量
                int l = -1, r = dp.size();
                while (l + 1 < r) {
                    int mid = (l + r) / 2;
                    if (dp[mid].first > cur) r = mid;
                    else l = mid;
                }
                ndp.emplace_back(cur, pre[l + 1] % MOD);
            }
            dp.swap(ndp);
        }

        // 统计答案
        i64 ans = 0;
        for (auto& p : dp) {
            ans = (ans + p.second) % MOD;
        }
        return ans;
    }
};