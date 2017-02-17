
#define MAX 100
int dp[MAX];
//int x[] = {-7, 10, 9, 2, 3, 8, 8, 1};
//int x[] = {389, 207, 155, 300, 299, 170, 158, 65};
int x[] = {1, 2, 3, 4, 5, 4, 3, 2, 1, 10};
int N = (sizeof x / sizeof(int)) - 1;
void _reset() {
    memset(dp, -1, sizeof dp);
}

/**
 Index value of longest increasing subsequence in O(n^2) - Recursively with dp apporoach.
 Ultimately this recursive approach is not better than iterative as
 all sub problems are revisited.
 **/
int LIS(int i) {
    if(i == 0) return 1;
    if (dp[i] != -1) {
        return dp[i];
    }
    int ans = 1;
    for(int j = 0; j < i; j++) {
        if (x[i] > x[j]) {
            ans = max(ans, 1 + LIS(j));
        }
    }
    return dp[i] = ans;
}


/**
 Longest Increasing Subsequence Length of full array in O(n^2) - Iteratively with dp apporoach.
 **/

int pos;
int LIS() {
    _reset();
    dp[0] = 1;
    
    for(int i = 1; i <= N; i++) {
        int ans = 1;
        for(int j = 0; j < i; j++) {
            if(x[i] > x[j]) {
                ans = max(ans, 1 + dp[j]);
            }
        }
        dp[i] = ans;
    }
    
    int lis = 0;
    for(int i = 0; i <= N; i++) {
        if(dp[i] > lis) {
            lis = dp[i];
            pos = i; // track the last index of LIS (required to construct sequence)
        }
    }
    return lis;
}

/**
 Finding the sequence of LIS
 **/
vector <int> listSequence;
void sequence() {
    listSequence.clear();
    listSequence.push_back(x[pos]);
    for(int i = pos-1; i >= 0; i--) {
        if( x[i] < x[pos] &&  dp[i] == dp[pos] -1) {
            pos = i;
            listSequence.push_back(x[i]);
        }
    }
    for(int i = listSequence.size() -1; i >= 0; i--) cout << listSequence[i] << " ";
}

/**
 Longest Increasing Subsequence in O(nlogk) time
 Jane Alam Jan tutorial
 **/
int I[30];
int LisNlogk() {
    int i;
    memset(I, INT_MAX, sizeof I);
    I[0] = INT_MIN;
    
    int trackPosition = 0;
    int max = INT_MIN;
    for(i = 0; i <= N; i++ ) {
        int begin, end, mid;
        begin = 0;
        end = trackPosition;
        while( begin <= end ) {
            mid = ( begin + end ) / 2;
            if( I[mid] < x[i] )
                begin = mid + 1;
            else
                end = mid - 1;
        }
        // observe the binary search carefully, when the binary search ends
        // begin > end and we put our item in I[begin]
        I[begin] = x[i];
        dp[i] = begin; // storing the LIS of every position
        if(dp[i] > max) { // track the last index for later reconstruct the sequence
            max = dp[i];
            pos = i;
        }
        if( trackPosition < begin )
            trackPosition = begin;
    }
    return trackPosition;
}

int LdsNlogk() {
    // LDS can also be achieved by recersing the data array and then calculating LIS
    int i;
    memset(I, INT_MIN, sizeof I);
    I[0] = INT_MAX;
    
    int trackPosition = 0;
    int Max = INT_MIN;
    for(i = 0; i <= N; i++ ) {
        int begin, end, mid;
        begin = 0;
        end = trackPosition;
        while( begin <= end ) {
            mid = ( begin + end ) / 2;
            if( I[mid] > x[i] )
                begin = mid + 1;
            else
                end = mid - 1;
        }
        // observe the binary search carefully, when the binary search ends
        // begin > end and we put our item in I[begin]
        I[begin] = x[i];
        dp[i] = begin; // storing the LIS of every position
        if(dp[i] > Max) { // track the last index for later reconstruct the sequence
            Max = dp[i];
            pos = i;
        }
        if( trackPosition < begin )
            trackPosition = begin;
    }
    return trackPosition;
}

void decreasingSeq() {
    listSequence.clear();
    listSequence.push_back(x[pos]);
    for(int i = pos-1; i >= 0; i--) {
        if( x[i] > x[pos] &&  dp[i] == dp[pos] - 1) {
            pos = i;
            listSequence.push_back(x[i]);
        }
    }
    for(int i = listSequence.size() -1; i >= 0; i--) cout << listSequence[i] << " ";
}