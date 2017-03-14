// calculates number of substrings divisble by d
int solve(string const& num, int d) {
    int ans = 0;
    int n = (int)num.length();
    vector<vector<int>> dp(n, vector<int>(d, 0)); // dp[i][j] = number of substrings ended at i with remainder j (mod d)
    for(int i = 0; i < n; i++) {
        int digit = num[i] - '0';
        dp[i][digit % d]++;
        if(i > 0) {
            for(int j = 0; j < d; j++) {
                int r = (j * 10 + digit) % d;
                dp[i][r] += dp[i - 1][j];
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
solve("10888", 8) => 12
*/