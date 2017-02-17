int d(int n) {
    if(n == 2) return 1;
    if(n == 1) return 0;
    if(dp[n] != -1) return dp[n];
    return dp[n] = (n - 1) * (d(n - 1) + d(n - 2));
}