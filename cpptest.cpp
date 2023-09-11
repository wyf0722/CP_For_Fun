#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using ll = long long;
const ll mod = 1e9 + 7;

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

template <typename T>
void mydebug(const char* format, T t) {
    cout << format << "=" << to_string(t) << endl;
}

template <typename Head, typename... Tail>
void mydebug(const char* format, Head H, Tail... T) {
    while (*format != ',')
        cout << *format++;
    cout << "=" << to_string(H) << ",";
    mydebug(format + 1, T...);
}
// #define debug(...) mydebug(#__VA_ARGS__, __VA_ARGS__)
#define debug(...) cout << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)

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

class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        // courses[i] = [durationi, lastDayi]
        // time + durationi <= lastDayi
        sort(courses.begin(), courses.end(), [](auto& a, auto& b) {
            return a[1] < b[1];
        }); // 按lastDay从小到大排序
        priority_queue<int> pq;
        int time = 0; // 时间戳
        for (auto& c: courses) {
            int dur = c[0], ld = c[1];
            if (time + dur <= ld) {
                // 这门课能上
                time += dur;
                pq.push(dur);
            } else if (!pq.empty() && pq.top() > dur){
                // 这门课不能上， 从之前上的课中挑选出duration最大的， 改上这门课
                time -= pq.top();
                pq.pop();
                time += dur;
                pq.push(dur);
            }
        }
        return pq.size();
    }
};

int main () {
    vector<int> v{1, 3, 34123, 2};
    pair<int, int> p{1, 8};
    debug(v, p);
}