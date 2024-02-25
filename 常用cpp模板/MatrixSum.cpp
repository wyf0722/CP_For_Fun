class MatrixSum {
private:
    vector<vector<int>> sum;

public:
    MatrixSum(vector<vector<int>> &matrix) {
        int m = matrix.size(), n = matrix[0].size();
        sum = vector<vector<int>>(m + 1, vector<int>(n + 1));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                sum[i + 1][j + 1] = sum[i + 1][j] + sum[i][j + 1] - sum[i][j] + matrix[i][j];
            }
        }
    }

    // 左闭，右开  左上角(x1,y1) 右下角(x2 - 1,y2 - 1)
    int query(int x1, int y1, int x2, int y2) {
        return sum[x2][y2] - sum[x1][y2] - sum[x2][y1] + sum[x1][y1];
    }
};