#include <iostream>

#define MAX 1000

class CatalanNumber {
public:
    int dp[MAX];
    
    void catalanNumber(int n) {
        dp[0] = dp[1] = 1;
        
        for(int k = 2; k <= n; ++k) {
            for(int i = 1; i <= k; ++i) {
                dp[k] += dp[i - 1] * dp[k - i];
            }
        }
        
    }
};

int main() {
}