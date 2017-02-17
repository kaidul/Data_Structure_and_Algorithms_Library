// Find minimum cost path from top-left corner to any bottom cell
int call(int i, int j) {
    if(isValid(i, j)) { //if still inside the array
        if(dp[i][j] != -1) return dp[i][j];
        int ret = INT_MIN;
        //try to move to 3 direction, also add current cell's point
        ret = max(ret, call(i + 1, j) + mat[i][j]);
        ret = max(ret, call(i + 1, j - 1) + mat[i][j]);
        ret = max(ret, call(i + 1, j + 1) + mat[i][j]);
        return dp[i][j] = ret;
    }
    
    return 0; //if outside the array
}