// 无向图tarjan
int n, t;
vector<vector<int>> g(n);
vector<int> dfn(n), low(n);
vector<vector<int>> bridges;

void tarjan(int x, int fa) {
    dfn[x] = low[x] = ++t;
    for (int y : g[x]) {
        if (y == fa)
            continue;
        if (!dfn[y]) {
            tarjan(y, x);
            low[x] = min(low[x], low[y]);
            if (dfn[x] < low[y]) {
                bridges.push_back({x, y});
            }
        } else {
            low[x] = min(low[x], dfn[y]);
        }
    }
}