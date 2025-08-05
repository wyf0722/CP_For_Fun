/*************************************************************************
    > File Name: A.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-08-06 00:31
************************************************************************/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isTrionic(vector<int>& nums) {
        int n = nums.size();
        if (nums[0] >= nums[1]) return false;
        int c = 1;
        for (int i = 2; i < n; i++) {
            if (nums[i] == nums[i - 1]) return false;
            if ((nums[i - 2] < nums[i - 1]) != (nums[i - 1] < nums[i])) c++;
        }
        return c == 3;
    }
};