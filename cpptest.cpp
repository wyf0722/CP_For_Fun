#include <bits/stdc++.h>

using namespace std;
const long long MOD = 1e9 + 7;

// int dx[4] = {1, 0, -1, 0};
// int dy[4] = {0, 1, 0, -1};

inline namespace DEBUG {
    string to_string(string s) {
        return '"' + s + '"';
    }

    string to_string(const char* s) {
        return to_string((string)s);
    }

    string to_string(bool b) {
        return (b ? "true" : "false");
    }

    template <typename A, typename B>
    string to_string(pair<A, B> p) {
        return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
    }

    template <typename A>
    string to_string(A v) {
        bool first = true;
        string res = "{";
        for (const auto& x : v) {
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

    template <typename Head, typename... Tail>
    void debug_out(Head H, Tail... T) {
        cout << " " << to_string(H);
        debug_out(T...);
    }

// #define debug(...) mydebug(#__VA_ARGS__, __VA_ARGS__)
#define debug(...)                                  \
    cout << __FUNCTION__ << ":" << __LINE__ << "->" \
         << " [" << #__VA_ARGS__ << "] =",          \
        debug_out(__VA_ARGS__)
}  // namespace DEBUG

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

#define yn(ans) printf("%s\n", (ans)?"Yes":"No");
#define YN(ans) printf("%s\n", (ans)?"YES":"NO");
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define rrep(i, a, b) for (int i = a; i >= b; i--)
using i64 = long long;
using ll = long long;
using vi = vector<int>;
using vii = vector<vector<int>>;
using pii = pair<int, int>;
template<class T> bool chmax(T &a, T b) {
	if (a >= b) return false;
	a = b; return true;
}
template<class T> bool chmin(T &a, T b) {
	if (a <= b) return false;
	a = b; return true;
}
class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();
        multiset<int> s;
        for (int x : nums)
            s.insert(x);
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            auto it = s.find(x);
            // s.erase(it);
            // 找到 x - limit <= y < x
            auto mx = s.lower_bound(x - limit);
            cout << *mx << endl;
            if (mx != s.end() && ((*mx) < x)) {
                ans[i] = *mx;
                s.erase(mx);
            } else {
                ans[i] = x;
                s.erase(it);
            }
        }
        return ans;
    }
};