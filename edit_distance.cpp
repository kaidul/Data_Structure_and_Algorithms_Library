int EditDistanceDP(string const& X, string const& Y) {
    int lenX = (int)X.length();
    int lenY = (int)Y.length();
    vector<vector<int> > dp(lenX + 1, vector<int>(lenY + 1, 0));
    for(int i = 0; i <= lenX; i++) dp[i][0] = i;
    for(int i = 0; i <= lenY; i++) dp[0][i] = i;
    for(int i = 1; i <= lenX; i++) {
        for(int j = 1; j <= lenY; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;
            }
        }
    }
    return dp[lenX][lenY];
}

// Recursive implementation
int EditDistanceRecursion( char *X, char *Y, int lenX, int lenY ) {
    // Base case 1: if both are empty string, no operation is needed
    if( lenX == 0 && lenY == 0 )
        return 0;
    // Base case 2: if one of the two strings is empty, then operation needed is equal to other non-empty string length
    if( lenX == 0 )
        return lenY;
    
    if( lenY == 0 )
        return lenX;
    
    // deletion
    int left = EditDistanceRecursion(X, Y, lenX - 1, lenY) + 1;
    // insertion
    int right = EditDistanceRecursion(X, Y, lenX, lenY - 1) + 1;
    // substitution or nothing
    int corner = EditDistanceRecursion(X, Y, lenX - 1, lenY - 1) + (X[lenX - 1] != Y[lenY - 1]);
    
    return min(left, min(right, corner));
}