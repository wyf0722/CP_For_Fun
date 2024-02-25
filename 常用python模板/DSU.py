class DSU:
    def __init__(self, n) -> None:
        self.fa = list(range(n))
        self.siz = [1] * n
    
    def find(self, x:int) -> int:
        while self.fa[x] != x:
            self.fa[x] = self.fa[self.fa[x]]
            x = self.fa[x]
        return x
        """
        if x == self.fa[x]:
            return x
        fa[x] = self.find(self.fa[x])
        return fa[x]
        """
    
    def merge(self, x:int, y:int) -> bool:
        x = self.find(x)
        y = self.find(y)
        if x == y:
            return False
        self.fa[y] = x
        self.siz[x] += self.siz[y]
        return True

    def same(self, x:int, y:int) -> bool:
        return self.find(x) == self.find(y)
        
    def size(self, x:int) -> int:
        return self.siz[self.find(x)]
    