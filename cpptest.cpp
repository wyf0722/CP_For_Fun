#include <bits/stdc++.h>

using namespace std;
// const long long MOD = 1e9 + 7;

// int dx[4] = {1, 0, -1, 0};
// int dy[4] = {0, 1, 0, -1};


string to_string(string s) {
    return '"' + s + '"';
}

string to_string(const char *s) {
    return to_string((string) s);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

template<typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template<typename A>
string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto &x: v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

void debug_out() {
    cout << endl;
}

template<typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cout << " " << to_string(H);
    debug_out(T...);
}

// #define debug(...) mydebug(#__VA_ARGS__, __VA_ARGS__)
#define debug(...)                                  \
    cout << __FUNCTION__ << ":" << __LINE__ << "->" \
         << " [" << #__VA_ARGS__ << "] =",          \
        debug_out(__VA_ARGS__)


// struct ListNode {
//     int val;
//     ListNode* next;
//     ListNode(int x) : val(x), next(NULL) {}
// };

// struct TreeNode {
//     int val;
//     TreeNode* left;
//     TreeNode* right;
//     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
// };

/*
 * stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */

#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define rrep(i, a, b) for (int i = a; i >= b; i--)
using i64 = long long;
using ll = long long;
using vi = vector<int>;
using vii = vector<vector<int>>;
using pii = pair<int, int>;

class Solution {
public:
    int longestAwesome(string s) {
        int n = s.size();
        // 前缀和 and 状态压缩
        // mp记录状态出现的位置
        unordered_map<int, int> mp;
        mp[0] = -1;
        int cur = 0;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            cur ^= 1 << (s[i] - '0');
            // 所有位置奇偶性相同，或者只有一位奇偶性不同
            if (mp.count(cur)) {
                ans = max(ans, i - mp[cur]);
            } else {
                mp[cur] = i;
            }
            for (int j = 0; j < n; j++) {
                if (mp.count(cur ^ (1 << j))) {
                    ans = max(ans, i - mp[cur ^ (1 << j)]);
                }
            }
        }
        return ans;
    }
};      