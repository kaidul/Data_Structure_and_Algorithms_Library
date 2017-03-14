// calculates number of subsequences divisble by d
int solve(string const& num, int d) {
    int ans = 0;
    int n = (int)num.length();
    vector<vector<int>> dp(n, vector<int>(d, 0)); // dp[i][j] = number of subsequences ended at i with remainder j (mod d)
    for(int i = 0; i < n; i++) {
        int digit = num[i] - '0';
        dp[i][digit % d]++;
        for(int j = 0; j < i; j++) {
            for(int k = 0; k < d; k++) {
                int r = (k * 10 + digit) % d;
                dp[i][r] += dp[j][k];
            }
        }
        ans += dp[i][0];
        // if numbers with preceeding 0 aren't allowed except '0' itself
        /*
         if(digit == 0) {
         dp[i][digit % d]--;
         }
         */
    }
    return ans;
}

/*
solve("10888", 8) => 20
*/



// Top-down approach

int solveUtil(int indx, int mod, string const& num, int d, vector<vector<int>>& dp) {
    if(indx == (int)num.length()) {
        return (mod == 0);
    }
    if(dp[indx][mod] != -1) {
        return dp[indx][mod];
    }
    int ret = 0;
    int digit = num[indx] - '0';
    ret += solveUtil(indx + 1, (mod * 10 + digit) % d, num, d, dp);
    ret += solveUtil(indx + 1, mod, num, d, dp);
    
    return dp[indx][mod] = ret;
}

int solve(string const& num, int d) {
    int n = (int)num.length();
    vector<vector<int>> dp(n, vector<int>(d, -1));
    return solveUtil(0, 0, num, d, dp);
}

/*
solve("10888", 8) - 1 // minus 1 to exclude empty string counting
*/