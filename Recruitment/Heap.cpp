#include <bits/stdc++.h>
using namespace std;

#define left(i) (i * 2 + 1)
#define right(i) (i * 2 + 2)
#define parent(i) ((i - 1) / 2)
struct Heap {
    vector<int> tree;
    Heap(int n_ = 0) { tree.resize(n_); }
    Heap(vector<int> vals) {
        tree = vals;
        for (int i = tree.size() - 1; i >= 0; i--) {
            // 每当堆化一个节点后，以该节点为根节点的子树就形成一个合法的子堆
            down(i);
        }
    }
    bool isEmpty() { return tree.size() == 0; }
    void push(int val) {
        tree.push_back(val);
        up(tree.size() - 1);
    }
    int pop() {
        assert(tree.size() != 0);
        swap(tree[0], tree[tree.size() - 1]);
        int ans = tree.back();
        tree.pop_back();
        down(0);
        return ans;
    }
    // 从底部往上调整
    void up(int idx) {
        while (1) {
            int fa = parent(idx);
            if (fa < 0 || tree[fa] >= tree[idx]) {
                return;
            }
            swap(tree[idx], tree[fa]);
            idx = fa;
        }
    }
    // 从顶部向下调整
    void down(int idx) {
        while (1) {
            int mx_idx = idx;
            for (int son : {left(idx), right(idx)}) {
                if (son < tree.size() && tree[son] > tree[mx_idx]) {
                    mx_idx = son;
                }
            }
            if (mx_idx == idx) {
                return;
            }
            swap(tree[idx], tree[mx_idx]);
            idx = mx_idx;
        }
    }
    void clear() { tree.resize(0); }
};