// Problem: 3665. Twisted Mirror Path Count
// Difficulty: Medium
// Language: C++
#define MOD 1000000007

int uniquePaths(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize, n = gridColSize[0];

    // R[i][j]: ways to arrive at (i,j) moving right
    // D[i][j]: ways to arrive at (i,j) moving down
    static int R[501][501], D[501][501];
    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= n; j++)
            R[i][j] = D[i][j] = 0;

    // Start is an empty cell with 1 way; seed its outgoing moves
    R[0][1] = 1;
    D[1][0] = 1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) continue;

            if (i == m - 1 && j == n - 1)
                return (int)(((long long)R[i][j] + D[i][j]) % MOD);

            if (grid[i][j] == 0) {
                int tot = (R[i][j] + D[i][j]) % MOD;
                if (j + 1 < n) R[i][j + 1] = (R[i][j + 1] + tot) % MOD;
                if (i + 1 < m) D[i + 1][j] = (D[i + 1][j] + tot) % MOD;
            } else {
                // moving right into mirror -> turned down
                if (i + 1 < m) D[i + 1][j] = (D[i + 1][j] + R[i][j]) % MOD;
                // moving down into mirror -> turned right
                if (j + 1 < n) R[i][j + 1] = (R[i][j + 1] + D[i][j]) % MOD;
            }
        }
    }
    return 0;
}
