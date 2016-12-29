int dp[MAX][MAX]; // dp[i][j] is number of ways j items can be choosen from i items

void ncr() {
	dp[0][0] = 1;
    for(int i = 1; i < MAX; ++i) {
        for(int j = 0; j <= i; ++j) {
            if(j == i or j == 0) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % mod;
            }
        }
    }
}