int LCS(string const& sA, string const& sB) {
    int lenA = (int)sA.length();
    int lenB = (int)sB.length();
    vector<vector<int> > dp(lenA + 1, vector<int>(lenB + 1, 0));
    for(int i = 0; i <= lenA; i++) dp[i][0] = 0;
    for(int i = 0; i <= lenB; i++) dp[0][i] = 0;
    for(int i = 1; i <= lenA; i++) {
        for(int j = 1; j <= lenB; j++) {
            if(sA[i - 1] == sB[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[lenA][lenB];
}