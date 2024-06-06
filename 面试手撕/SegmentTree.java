class SegmentTree<T> {
    // 原始数据
    private T[] data;
    // 区间信息
    private T[] tree;
    // 区间合并 merge
    private BiFunction<T, T, T> merge;

    public SegmentTree(T data[], BiFunction<T, T, T> function) {
        Objects.requireNonNull(function);
        this.data = data;
        int size = 4 * data.length;
        tree = (T[]) new Object[size];
        this.merge = (x1, x2) -> {
            if (x1 == null) return x2;
            if (x2 == null) return x1;
            return function.apply(x1, x2);
        };
        build(1, 0, data.length);
    }

    private void pull(int p) {
        tree[p] = merge.apply(tree[p * 2], tree[p * 2 + 1]);
    }

    private void build(int p, int l, int r) {
        if (r - l == 1) {
            tree[p] = data[l];
            return;
        }
        int mid = (l + r) / 2;
        build(p * 2, l, mid);
        build(p * 2 + 1, mid, r);
        pull(p);
    }

    public void modify(int pos, T x) {
        data[pos] = x;
        modify(1, 0, data.length, pos);
    }

    private void modify(int p, int l, int r, int pos) {
        if (r - l == 1) {
            tree[p] = data[pos];
            return;
        }
        int mid = (l + r) / 2;
        if (pos < mid) {
            modify(p * 2, l, mid, pos);
        } else {
            modify(p * 2 + 1, mid, r, pos);
        }
        pull(p);
    }

    public T rangeQuery(int lo, int hi) {
        return rangeQuery(1, 0, data.length, lo, hi);
    }

    private T rangeQuery(int p, int l, int r, int lo, int hi) {
        if (l >= hi || r <= lo) return null;
        if (lo <= l && hi >= r) return tree[p];
        int mid = (l + r) / 2;
        T leftResult = rangeQuery(p * 2, l, mid, lo, hi);
        T rightResult = rangeQuery(p * 2 + 1, mid, r, lo, hi);
        return merge.apply(leftResult, rightResult);
    }
}


// template for range sum
BiFunction<Integer, Integer, Integer> sum = (a, b) -> a + b;
Integer[] nums = new Integer[n];
SegmentTree<Integer> segmentTree = new SegmentTree(nums, sum);
