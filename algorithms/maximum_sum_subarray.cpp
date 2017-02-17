/**
 Maximum Sum O(n^4)
 Logic:
 ---------
 1. Array[i, j] no longer contains its own value, but the sum of all within sub-rectangle (0, 0) and (i, j). this is done while taking input in O(n^2)
 2. Then we can calculate the sum of any sub-rectangle (i, j) to (k, l) in O(1)
 3. For (1, 2) & (3, 3), the sum is = Array[3, 3] - Array[0, 3] - Array[3, 1] + Array[0, 1]
 4. To calculate the maximum sum, we need to calculate all the sum from (0, 0) to (n, n) and filter the maximum one.
 **/
#define MAX 1000
int maxSum() {
    int row, col;
    int M[MAX + 10][MAX + 10];
    scanf("%d %d", &row, &col);
    
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            scanf("%d", &M[i][j]);
            if(i > 0) M[i][j] += M[i - 1][j];
            if(j > 0) M[i][j] += M[i][j - 1];
            // M[i -1][j - 1] is included both in M[i][j - 1] & M[i - 1][j]. So we need to exclude one.
            if(i > 0 && j > 0) M[i][j] -= M[i - 1][j - 1]; // inclusion-exclusion principle
        }
    }
    
    int maxSum = INT_MIN, sum;
    for(int i = 0; i < row; i++) for(int j = 0; j < col; j++) // starting cordinate
    for(int k = i; k < row; k++) for(int l = j; l < col; l++) { // ending cordinate
        sum = M[k][l];
        if(i > 0) sum -= M[i - 1][l];
        if(j > 0) sum -= M[k][j - 1];
        if(i > 0 && j > 0) sum += M[i - 1][j - 1]; // inclusion-exclusion principle
        maxSum = max(maxSum, sum);
    }
    return maxSum;
}

/* O(n^3) */
long maxSum2() {
    int row, col;
    int M[MAX + 10][MAX + 10];
    scanf("%d %d", &row, &col);
    
    //contains sum of all values of column 1 up to row n
    for(int i = 1; i <= row; i++) for(int j = 1; j <= col; j++) {
        scanf("%d", &M[i][j]);
        M[i][j] += M[i - 1][j]; // cumultive sum of columns [1 2 3 4 5] => [1 3 6 10 15]
    }
    
    long ans = M[1][1];
    
    for(int i = 1; i <= row; i++) {
        for(int j = i + 1; j <= row; j++) {
            long tmp = 0;
            for(int k = 1; k <= col; k++) {
                tmp += (M[j][k] - M[i][k]);
                ans = max(ans, tmp);
                if(tmp < 0) tmp = 0;
            }
        }
    }
    return ans;
}