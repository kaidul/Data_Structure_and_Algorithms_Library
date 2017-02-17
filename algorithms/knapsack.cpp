// classic knapsack problem.
#define MAXN 100
#define MAXW 1000
int n;
int dp[MAXN + 1][MAXW + 1];
int weight[MAXN + 1];
int price[MAXN + 1];
int capacity;

// top down approach
int knapsack(int i, int w) {
    if(i == n) {
        return 0;
    }
    if(dp[i][w] != -1) {
        return dp[i][w];
    }
    int profit1 = 0, profit2 = 0;
    if(w + weight[i] <= capacity) {
        profit1 = price[i] + knapsack(i + 1, w + weight[i]);
    }
    
    profit2 = knapsack(i + 1, w);
    
    return dp[i][w] = max(profit1, profit2);
}

// bottom up approach (better approach)
int dp[MAXW + 1];
void solve(int n, int capacity) {
    for (int i = 0; i < n; i++) {
        for (int j = capacity; j >= 0; j--) {
            if(weight[i] <= j) {
                dp[j] = max(dp[j], dp[j - weight[i]] + price[i]);
            }
        }
    }
}