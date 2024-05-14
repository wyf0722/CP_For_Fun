#include <bits/stdc++.h>
using namespace std;

void merge_sort(vector<int>& v, int l, int r) {
    if (l >= r)
        return;
    int mid = l + ((r - l) >> 1);
    merge_sort(v, l, mid);
    merge_sort(v, mid + 1, r);
    vector<int> tmp(r - l + 1);
    int now = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r) {
        if (v[i] < v[j]) {
            tmp[now++] = v[i++];
        } else {
            tmp[now++] = v[j++];
        }
    }
    while (i <= mid)
        tmp[now++] = v[i++];
    while (j <= r)
        tmp[now++] = v[j++];
    for (int idx = 0; idx < r - l + 1; idx++) {
        v[l + idx] = tmp[idx];
    }
}