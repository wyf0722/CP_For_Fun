from collections import defaultdict
class DSU:
    def __init__(self, n: int) -> None:
        self.root_or_size = [-1] * n
        self.part = n
        self.n = n
        return

    def initialize(self):
        for i in range(self.n):
            self.root_or_size[i] = -1
        self.part = self.n
        return

    def find(self, x):
        y = x
        while self.root_or_size[x] >= 0:
            # range_merge_to_disjoint to the direct root node after query
            x = self.root_or_size[x]
        while y != x:
            self.root_or_size[y], y = x, self.root_or_size[y]
        return x

    def merge(self, x, y):
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x == root_y:
            return False
        if self.root_or_size[root_x] < self.root_or_size[root_y]:
            root_x, root_y = root_y, root_x
        self.root_or_size[root_y] += self.root_or_size[root_x]
        self.root_or_size[root_x] = root_y
        self.part -= 1
        return True

    def merge_left(self, x, y):
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x == root_y:
            return False
        self.root_or_size[root_x] += self.root_or_size[root_y]
        self.root_or_size[root_y] = root_x
        self.part -= 1
        return True

    def merge_right(self, x, y):
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x == root_y:
            return False
        self.root_or_size[root_y] += self.root_or_size[root_x]
        self.root_or_size[root_x] = root_y
        self.part -= 1
        return True

    def merge_max(self, x, y):
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x == root_y:
            return False
        if root_x > root_y:
            root_x, root_y = root_y, root_x
        self.root_or_size[root_y] += self.root_or_size[root_x]
        self.root_or_size[root_x] = root_y
        self.part -= 1
        return

    def merge_min(self, x, y):
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x == root_y:
            return False
        if root_x < root_y:
            root_x, root_y = root_y, root_x
        self.root_or_size[root_y] += self.root_or_size[root_x]
        self.root_or_size[root_x] = root_y
        self.part -= 1
        return

    def same(self, x, y):
        return self.find(x) == self.find(y)

    def size(self, x):
        return -self.root_or_size[self.find(x)]

    def get_root_part(self):
        # get the nodes list of every root
        part = defaultdict(list)
        n = len(self.root_or_size)
        for i in range(n):
            part[self.find(i)].append(i)
        return part

    def get_root_size(self):
        # get the size of every root
        size = defaultdict(int)
        n = len(self.root_or_size)
        for i in range(n):
            if self.find(i) == i:
                size[i] = -self.root_or_size[i]
        return size
