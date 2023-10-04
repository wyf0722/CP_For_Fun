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
#ifdef LOCAL
#define debug(...)                                    \
    cout << "\033[1;31m" << __FUNCTION__ << "\033[0m" \
         << ":"                                       \
         << "\033[1;32m" << __LINE__ << "\033[0m"     \
         << "->"                                      \
         << "[" << #__VA_ARGS__ << "] =",             \
        debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif
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

/*###########################################
#############################################
#######      Solution    ####################
#############################################
#############################################*/

int main() {
    int a = 1;
    debug(a);
}