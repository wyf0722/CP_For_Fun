/*************************************************************************
    > File Name: B.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-03-16 01:22
************************************************************************/
#include <bits/stdc++.h>
using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#define debug(...) cout << '[' << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

class Spreadsheet {
    pair<int, int> parse(string cell) {
        if (isdigit(cell[0])) return {-1, stoi(cell)};
        return {cell[0] - 'A', stoi(cell.substr(1)) - 1};
    };
public:
    vector<vector<int>> g;
    Spreadsheet(int rows) {
        g = vector<vector<int>>(26, vector<int>(rows));
    }
    
    void setCell(string cell, int value) {
        auto [i, j] = parse(cell);
        g[i][j] = value;
    }
    
    void resetCell(string cell) {
        setCell(cell, 0);
    }
    
    int getValue(string formula) {
        int idx = formula.find('+');
        string cell1 = formula.substr(1, idx - 1);
        string cell2 = formula.substr(idx + 1);
        int ans = 0;
        for (auto cell : {cell1, cell2}) {
            auto [i, j] = parse(cell);
            ans += i == -1 ? j : g[i][j];
        }
        return ans;
    }
};

/**
 * Your Spreadsheet object will be instantiated and called as such:
 * Spreadsheet* obj = new Spreadsheet(rows);
 * obj->setCell(cell,value);
 * obj->resetCell(cell);
 * int param_3 = obj->getValue(formula);
 */