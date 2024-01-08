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


/**
 * https://github.com/Joshc88/CPTemplates/blob/main/Graph/bfs.h
 * directed: True(有向图) False(无向图)
*/
template <bool directed = true> struct BFS { // 0 or 1-indexed, doesn't matter
    int n;
    vector<vector<int>> edges;

    BFS() {}

    BFS(int N) {
        n = N;
        edges.resize(n+1);
    }

    void add_edge(int from, int to) {
        edges[from].push_back(to);
        if (!directed) edges[to].push_back(from);
    }

    vector<int> dist(vector<int> sources) {
        vector<int> res(n+1, -1);
        queue<int> q;
        for (int i : sources) {
            res[i] = 0;
            q.push(i);
        }
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int i : edges[cur]) {
                if (res[i] == -1) {
                    res[i] = res[cur]+1;
                    q.push(i);
                }
            }
        }
        return res;
    }

    int dist(int source, int dest) {
        return dist({source})[dest];
    }

    pair<int, vector<int>> path(int source, int dest) {
        vector<int> res(n+1, -1);
        vector<int> before(n+1);
        queue<int> q;
        res[source] = 0;
        q.push(source);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int i : edges[cur]) {
                if (res[i] == -1) {
                    res[i] = res[cur]+1;
                    before[i] = cur;
                    q.push(i);
                }
            }
        }
        if (res[dest] == -1) return make_pair(-1, vector<int>());
        vector<int> path = {dest};
        while (path.back() != source) path.push_back(before[path.back()]);
        reverse(path.begin(), path.end());
        return make_pair(res[dest], path);
    }
};

class Solution {
public:
    int minimumOperationsToMakeEqual(int x, int y) {
        int N = max(x, y) * 12;
        BFS g(N);
        for (int i = 1; i <= N; i++) {
            if (i % 5 == 0) g.add_edge(i, i / 5);
            if (i % 11 == 0) g.add_edge(i, i / 11);
            if (i < N) g.add_edge(i, i + 1);
            if (i) g.add_edge(i, i - 1);
        }
        return g.dist(x, y);
    }
};