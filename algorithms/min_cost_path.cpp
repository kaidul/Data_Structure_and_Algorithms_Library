/* Given a cost matrix cost[][] and a position (m, n) in cost[][],
 write a function that returns cost of minimum cost path to reach (m, n) from (0, 0) */
// allowed path in down or right
int minCost(vector<vector<int>>& cost, int m, int n) {
    int R = (int)cost.size();
    int C = (int)cost[0].size();
    // Instead of following line, we can use int cache[m+1][n+1] or
    // dynamically allocate memoery to save space. The following line is
    // used to keep te program simple and make it working on all compilers.
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    
    dp[0][0] = cost[0][0];
    
    /* Initialize first column of total cost(dp) array */
    for (int i = 1; i <= m; i++) {
        dp[i][0] = dp[i - 1][0] + cost[i][0];
    }
    
    /* Initialize first row of cache array */
    for (int j = 1; j <= n; j++) {
        dp[0][j] = dp[0][j - 1] + cost[0][j];
    }
    
    /* Construct rest of the cache array */
    for (int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]) + cost[i][j];
        }
    }
    
    return dp[m][n];
}
