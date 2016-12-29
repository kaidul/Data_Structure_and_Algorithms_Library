// Returns the length of the longest palindromic subsequence in seq
int lps(string const& s) {
    int n = (int)s.length();
    // Strings of length 1 are palindrome of length 1
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++) dp[i][i] = 1;
    
    /* Build the table. Note that the lower diagonal values of table are
     useless and not filled in the process. The values are filled in a
     manner similar to MCM. */
    for(int len = 2; len <= n; len++) {
        for (int i = 0; i < n - len + 1; i++) {
            int j = i + len - 1;
            if (s[i] == s[j] and len == 2) {
                dp[i][j] = 2;
            }
            else if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            }
            else {
                dp[i][j] = max(dp[i][j - 1], dp[i + 1][j]);
            }
        }
    }
    
    return dp[0][n - 1];
}