class ST2D:
    """二维稀疏表（ST表），支持O(1)查询子矩阵最大值"""
    def __init__(self, matrix: list[list[int]]):
        self.matrix = matrix
        self.n = len(matrix)
        self.m = len(matrix[0]) if self.n else 0
        
        # 预处理最大层数
        self.logn = self.n.bit_length()
        self.logm = self.m.bit_length()
        
        # 初始化ST表：st[k1][k2][i][j]
        self.st = [
            [[[0]*self.m for _ in range(self.n)] 
             for __ in range(self.logm)] 
            for ___ in range(self.logn)
        ]
        
        # 初始化k1=0, k2=0（原矩阵）
        for i in range(self.n):
            for j in range(self.m):
                self.st[0][0][i][j] = matrix[i][j]
        
        # 预处理行方向（k1=0）
        for k2 in range(1, self.logm):
            step = 1 << (k2 - 1)
            for i in range(self.n):
                for j in range(self.m - (1 << k2) + 1):
                    self.st[0][k2][i][j] = max(
                        self.st[0][k2-1][i][j],
                        self.st[0][k2-1][i][j+step]
                    )
        
        # 预处理列方向
        for k1 in range(1, self.logn):
            step = 1 << (k1 - 1)
            for k2 in range(self.logm):
                for i in range(self.n - (1 << k1) + 1):
                    for j in range(self.m - (1 << k2) + 1):
                        self.st[k1][k2][i][j] = max(
                            self.st[k1-1][k2][i][j],
                            self.st[k1-1][k2][i+step][j]
                        )

    def query_max(self, r1: int, c1: int, r2: int, c2: int) -> int:
        """
        查询 [r1, r2) × [c1, c2) 左闭右开区间内的最大值
        自动越界保护，超出矩阵范围会自动截断
        """
        # 越界保护
        r1 = max(r1, 0)
        c1 = max(c1, 0)
        r2 = min(r2, self.n)
        c2 = min(c2, self.m)
        
        if r1 >= r2 or c1 >= c2:
            return -float('inf')  # 空矩阵返回极小值
        
        # 计算层数
        k1 = (r2 - r1).bit_length() - 1
        k2 = (c2 - c1).bit_length() - 1
        
        # 四个角覆盖整个区间
        return max(
            self.st[k1][k2][r1][c1],
            self.st[k1][k2][r2 - (1 << k1)][c1],
            self.st[k1][k2][r1][c2 - (1 << k2)],
            self.st[k1][k2][r2 - (1 << k1)][c2 - (1 << k2)]
        )

class Solution:
    def countLocalMaximums(self, matrix: list[list[int]]) -> int:
        if not matrix or not matrix[0]:
            return 0
        
        # 初始化二维ST表
        st = ST2D(matrix)
        n, m = len(matrix), len(matrix[0])
        ans = 0
        
        for i in range(n):
            for j in range(m):
                x = matrix[i][j]
                if x <= 0:
                    continue
                
                # 题目要求的两个菱形区域查询
                max1 = st.query_max(i - x, j - x + 1, i + x + 1, j + x)
                max2 = st.query_max(i - x + 1, j - x, i + x, j + x + 1)
                
                if max(max1, max2) <= x:
                    ans += 1
        
        return ans
        