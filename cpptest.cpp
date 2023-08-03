#include "leetcode.h"
class Solution {
public:
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        int n = edges.size();
        vector<bool> vis(n, false);
        vector<int> dis(n, -1);
        for (int i = node1, cnt = 0; i >= 0 && vis[i] == false; i = edges[i], cnt++) {
            dis[i] = cnt;
        }
        fill(vis.begin(), vis.end(), false);
        int ans, d;
        for (int i = node2, cnt = 0; i >= 0 && vis[i] == false; i = edges[i], cnt++) {
            // node1能到达
            if (dis[i] != -1) {
                if (max(dis[i], cnt) < d) {
                    d = max(dis[i], cnt);
                    ans = i;
                } else if (max(dis[i], cnt) == d) {
                    ans = min(ans, i);
                }
            }
        }
        return ans;
    }
};

int main() {
    // Solution sol;
    // string str = "dnfad";
    // auto cur = sol.;
    // cout << to_string(cur);
    return 0;
}
