// Digit DP
// Count how many numbers are there between A and B inclusive which sum of digits is divisble by K
#define BIT_LENGTH_64 64
#define MAX_REMAINDER 5 // can be 0, 1, 2 ... K - 1 only

i64 dp[BIT_LENGTH_64][MAX_REMAINDER];
bool visited[BIT_LENGTH_64][MAX_REMAINDER];
i64 A, B;
int K; // 5

i64 solveUtil(int depth, int remainder) {
    if(depth == 0) {
        return (remainder == 0);
    }
    if(visited[depth][remainder]) {
        return dp[depth][remainder];
    }
    i64 ret = 0LL;
    for(int d = 0; d <= 9; ++d) {
        ret += solveUtil(depth - 1, (remainder + d) % K);
    }
    visited[depth][remainder] = true;
    return dp[depth][remainder] = ret;
}

i64 solve(i64 N) {
    if(N < 0LL) return 0LL;
    char buffer[BIT_LENGTH_64];
    sprintf(buffer, LLD, N);
    int len = (int)strlen(buffer);
    int remainder = 0;
    int depth = len;
    i64 ret = 0LL;
    for(int i = 0; i < len; ++i) {
        int digit = buffer[i] - '0';
        for(int d = 0; d < digit; ++d) {
            ret += solveUtil(depth - 1, (remainder + d) % K);
        }
        depth--;
        remainder = (remainder + digit) % K;
    }
    ret += (remainder == 0);
    return ret;
}

// solve(B) - solve(A - 1LL)