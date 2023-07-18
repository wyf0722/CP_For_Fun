#include "leetcode.h"

class Solution {
public:
    bool makeStringsEqual(string s, string t) {
        // 0 0 -> 0 0 只有零 无变化
        // 0 1 -> 1 1 
        // 1 1 -> 1 0
        // 01两次操作可以形成交换操作
        // 1最少只能减少到1个
        // 只要有
        int s0 = 0, s1 = 0, t0 = 0, t1 = 0;
        for (char c: s) {
            if (c == '0') s0++;
            else s1++;
        }
        for (char c: t) {
            if (c == '0') t0++;
            else t1++;
        }
        // 考虑首先使得1的数量相同

        // // 全0 不能形成 含1
        // if (s1 == 0 && t1) return false;
        // // 全1 不能形成 全0
        // if (s0 == 0 && t1 == 0) return false;

        // // 有0有1 不能形成 全0
        // if (s0 && s1 && t1 == 0) return false;

        // s无1 t有1       s有1 t无1
        return (s1 > 0) == (t1 > 0);
    }
};




















int main() {
<<<<<<< HEAD
    cout << __gcd(0, 7) << endl;
    cout << __gcd(4, 6) << endl;
=======
    Solution sol;
    string str = "dnfad";
    cout << str << endl;
    vector<string> v;
    v.emplace_back(move(str));
    cout << str << endl;
>>>>>>> 847f568c9aecaf14cc28a220b380f5a3605d211d
    return 0;
}