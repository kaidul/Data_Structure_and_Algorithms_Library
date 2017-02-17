/**
 
http://www.geeksforgeeks.org/dynamic-programming-set-8-matrix-chain-multiplication/
 
Time Complexity: O(n^3)
Auxiliary Space: O(n^2)
**/
// Matrix Ai has dimension p[i-1] x p[i] for i = 1..n
int MatrixChainOrder(vector<int>& p) {
 
    /* For simplicity of the program, one extra row and one extra column are
       allocated in m[][].  0th row and 0th column of m[][] are not used */
    int n = (int)p.size();
    vector<vector<int>> dp(n, vector<int>(n));
 
    /* m[i,j] = Minimum number of scalar multiplications needed to compute
       the matrix A[i]A[i+1]...A[j] = A[i..j] where dimention of A[i] is
       p[i-1] x p[i] */
 
    // cost is zero when multiplying one matrix.
    for (int i = 1; i < n; i++) {
        dp[i][i] = 0;
    }
 
    // L is chain length.
    for (int len = 2; len < n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
 
    return dp[1][n - 1];
}