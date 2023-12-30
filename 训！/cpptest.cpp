#include <bits/stdc++.h>

using namespace std;

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

#define debug(...)                                  \
    cout << __FUNCTION__ << ":" << __LINE__ << "->" \
         << " [" << #__VA_ARGS__ << "] =",          \
        debug_out(__VA_ARGS__)

/*
 *             _       _   _                      __                   __
 *   ___  ___ | |_   _| |_(_) ___  _ __     ___  / _| __      ___   _ / _|
 *  / __|/ _ \| | | | | __| |/ _ \| '_ \   / _ \| |_  \ \ /\ / / | | | |_
 *  \__ \ (_) | | |_| | |_| | (_) | | | | | (_) |  _|  \ V  V /| |_| |  _|
 *  |___/\___/|_|\__,_|\__|_|\___/|_| |_|  \___/|_|     \_/\_/  \__, |_|
 *                                                              |___/
 */

#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define rrep(i, a, b) for (int i = a; i >= b; i--)
using i64 = long long;
using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using vll = vector<vector<ll>>;
using vii = vector<vector<int>>;
using pii = pair<int, int>;
const int inf = INT_MAX / 2 - 100;
const i64 infLL = LLONG_MAX / 3;
const long long MOD = 1e9 + 7;
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};
template <class T>
bool chmin(T& a, const T& b) {
    return b < a ? a = b, 1 : 0;
}  // set a = min(a,b)
template <class T>
bool chmax(T& a, const T& b) {
    return a < b ? a = b, 1 : 0;
}  // set a = max(a,b)

