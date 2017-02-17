// Returns true if there is a subset of set[] with sun equal to given sum
bool isSubsetSum(vector<int>& set, int sum)
{
    // The value of subset[i][j] will be true if there is a subset of set[0..j-1]
    //  with sum equal to i
    int n = (int)set.size();
    vector<vector<bool>> dp(sum + 1, vector<bool>(n));
    
    // If sum is 0, then answer is true
    for (int i = 0; i < n; i++) dp[0][i] = true;
    
    // If sum is not 0 and set is empty, then answer is false
    for (int i = 1; i <= sum; i++) dp[i][0] = false;
    
    // Fill the subset table in botton up manner
    for (int i = 1; i <= sum; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = dp[i][j - 1];
            if (i - set[j] >= 0) {
                dp[i][j] = dp[i][j] | dp[i - set[j]][j - 1];
            }
        }
    }
    
    /*
    // uncomment this code to print table
     for (int i = 0; i <= sum; i++) {
        for (int j = 0; j <= n; j++)
            printf ("%4d", subset[i][j]);
        printf("\n");
     } 
     */
    
    return dp[sum][n];
}