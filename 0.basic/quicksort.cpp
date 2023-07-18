#include "..\leetcode.h"

template <typename T>
void QuickSort(vector<T>& v, int l, int r) {
    if (l > r)
        return;
    T key = v[l];
    int i = l, j = r;
    while (i < j) {
        // Find the first number less than key from right
        while (i < j && key <= v[j])
            j--;
        // Find the first number greater than key from left to right
        while (i < j && key >= v[i])
            i++;
        if (i < j) {
            swap(v[i], v[j]);
        }
    }
    swap(v[l], v[i]);
    QuickSort(v, l, i - 1);
    QuickSort(v, i + 1, r);
}

template <typename T>
void QuickSort2(vector<T>& v, int l, int r) {
    if (l > r)
        return;
    // Dig a pit in the first element number
    int i = l, j = r;
    T key = v[l];
    while (i < j) {
        while (i < j && key <= v[j])
            j--;
        if (i < j)
            v[i++] = v[j];
        while (i < j && key >= v[i])
            i++;
        if (i < j)
            v[j--] = v[i];
    }
    v[i] = key;
    QuickSort2(v, l, i - 1);
    QuickSort2(v, i + 1, r);
}

template <typename T>
void QuickSort3(vector<T>& v, int l, int r) {
    if (l > r)
        return;
    // taking the last element as pivot
    T key = v[r];
    int i = l - 1;
    // Consider the elements in the R-1 range, move the elements smaller than the key to the front
    for (int j = l; j < r; j++) {
        if (v[j] < key) {
            i++;
            swap(v[i], v[j]);
        }
    }
    v[i + 1] = key;
    QuickSort3(v, l, i);
    QuickSort3(v, i + 2, r);
}

int main() {
    vector<int> nums = {1, 23, 3, 5, 6, 5, 8, 9};
    // assert(is_sorted(nums.begin(), nums.end()));
    QuickSort3(nums, 0, nums.size() - 1);
    cout << to_string(nums) << endl;
    vector<string> strs = {"abc", "fsa", "dsfade", "ab", "ab", "zzq"};
    QuickSort3(strs, 0, strs.size() - 1);
    cout << to_string(strs) << endl;
}