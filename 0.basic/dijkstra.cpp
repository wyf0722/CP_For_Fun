#include "..\leetcode.h"

/**
 * 节点编号从1开始
*/
#define Inf 0x3f3f3f3f
#define MaxVertex 100

int g[MaxVertex][MaxVertex]; // 邻接矩阵
int dis[MaxVertex]; // 距离
int vis[MaxVertex]; // 是否访问过
int pre[MaxVertex]; // 前驱节点
int n, m; // 节点个数 ans 边的个数

// 初始化图的信息 建立邻接矩阵
void init() {
    // 顶点
    cout << "input the number of vertexs: ";
    cin >> n;
    memset(g, Inf, sizeof(g));
    for (int i = 1; i <= n; i++)
        g[i][i] = 0;
    // 边
    cout << "input the number of edges: ";
    cin >> m;
    int from, to, weight;
    for (int i = 0; i < m; i++) {
        cout << "from--to--weight: ";
        cin >> from >> to >> weight;
        g[from][to] = weight;
    }
}

void Dijkstra(int begin) {
    memset(dis, Inf, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    memset(pre, -1, sizeof(pre));

    dis[begin] = 0; // 到自身距离为0
    // pre[begin] = begin; // 源点的前驱节点设置为自身
    for (int i = 0; i < n; i++) {
        // 寻找最短路径对应的节点
        int minV = 0;
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && dis[j] < dis[minV])
                minV = j;
        }
        // 从begin能到达的节点已经全部被update
        if (minV == 0)
            return;
        vis[minV] = 1;
        for (int j = 1; j <= n; j++)
            if (!vis[j])
                if (dis[minV] + g[minV][j] < dis[j]) {
                    dis[j] = dis[minV] + g[minV][j];
                    pre[j] = minV;
                }
    }
}

void output(int begin) {
    for (int i = 1; i <= n; i++) {
        if (dis[i] == Inf) {
            printf("from %d to %d, there is no path\n", begin, i);
        } else {
            printf("from %d to %d, the shortest path = ", begin, i);
            stack<int> s;
            int x = i;
            while(x != -1) {
                s.push(x);
                x = pre[x];
            }
            cout << s.top();
            s.pop();
            while(!s.empty()) {
                cout << "--" << s.top();
                s.pop();
            }
            cout << ", and length = " << dis[i] << endl;
            
        }
    }
}

int main() {
    init();
    Dijkstra(4);
    output(4);
    return 0;
}