#define MAXM 10
#define MAXN 10
int coin[MAXN];
long long make, dp[MAXN][MAXM];

/* If # of coins is un-changeable */
// top-down approach
long long coinChange(int i, long long amount) {    
    if(i >= MAXM) {
        return (0 == amount);
    }
    if(dp[i][amount] != -1) {
        return dp[i][amount];
    }
    
    long long with = 0LL, without = 0LL;
    
    if(amount - coin[i] >= 0) {
        with = coinChange(i, amount - coin[i]);
    }
    
    without = coinChange(i + 1, amount);
    
    return dp[i][amount] = with + without;
    // return dp[i][amount] = ret1 | ret2;
}


// bottom-up approach
long long dp[MAXM];
void solve(int n, int m) {
    dp[0] = 1;
    for(int i = 0; i < n; i++) {
        for(int j = m; j > 0; j--) {
            if(j - coins[i] >= 0) {
                dp[j] += dp[j - coins[i]];
            }
        }
    }
}

/* for consecutive coin i.e. 1, 2, 3, 4, 5, 6.... this top-down approach suffices */
void solve() {
    memset(dp, 0, sizeof dp);
    cache[0] = 1;
    for(int i = 1; i <= MAXM; i++) {
        for(int j = i; j <= MAXM; j++) {
            dp[j] += dp[j - i];
        }
    }
}

// coins can be taken multiple times
// permutation not allowed
void solve2(int n, int m) {
    dp[0] = 1;
    for(int i = 0; i < n; i++) {
        for(int j = 1; j <= m; j++) {
            if(j - coins[i] >= 0) {
                dp[j] += dp[j - coins[i]];
            }
        }
    }
}

// coins can be taken multiple times
// [2, 3] and [3, 2] both are counted
void solve3(int n, int m) {
    dp[0] = 1;
    for(int i = 1; i <= m; i++) {
        for(int j = 0; j < n; j++) {
            if(i - coins[j] >= 0) {
                dp[i] += dp[i - coins[j]];
            }
        }
    }
}