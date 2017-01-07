// maximum contiguous sum of an array
int kadane(vector<int>& arr, int& left, int& right) {
    int result = INT_MIN, currSum = 0;
    int n = (int)arr.size();
    left = 0;
    for(int i = 0; i < n; i++) {
        currSum += arr[i];
        
        if(currSum < 0) {
            currSum = 0;
            left = i + 1;
        }
        
        if(currSum > result) {
            right = i;
            result = currSum;
        }
    }
    return result;
}


// Find Maximum subarray sum in O(n^3) using Kadane algorithm
void findMaxSum(vector<vector<int>>& M) {
    // Variables to store the final output
    int maxSum = INT_MIN, finalLeft, finalRight, finalTop, finalBottom;
    int m = (int)M.size();
    int n = (int)M[0].size();
    int left, right, i;
    int sum, start, finish;
    vector<int> tmp(m);
    
    // Set the left column
    for (left = 0; left < n; ++left) {
        // Initialize all elements of temp as 0
        memset(tmp, 0, sizeof(tmp));
        
        // Set the right column for the left column set by outer loop
        for (right = left; right < n; ++right) {
            // Calculate sum between current left and right for every row 'i'
            for (i = 0; i < m; ++i) {
                tmp[i] += M[i][right];
            }
            
            // Find the maximum sum subarray in temp[]. The kadane() function
            // also sets values of start and finish.  So 'sum' is sum of
            // rectangle between (start, left) and (finish, right) which is the
            //  maximum sum with boundary columns strictly as left and right.
            sum = kadane(tmp, start, finish);
            
            // Compare sum with maximum sum so far. If sum is more, then update
            // maxSum and other output values
            if (sum > maxSum) {
                maxSum = sum;
                finalLeft = left;
                finalRight = right;
                finalTop = start;
                finalBottom = finish;
            }
        }
    }
    
    // Print final values
    printf("(Top, Left) (%d, %d)\n", finalTop, finalLeft);
    printf("(Bottom, Right) (%d, %d)\n", finalBottom, finalRight);
    printf("Max sum is: %d\n", maxSum);
}