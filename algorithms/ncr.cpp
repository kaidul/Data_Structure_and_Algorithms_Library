int dp[MAX][MAX]; // dp[i][j] is number of ways j items can be choosen from i items

void ncr() {
	dp[0][0] = 1;
    for(int i = 1; i < MAX; ++i) {
        for(int j = 0; j <= i; ++j) {
            if(j == i or j == 0) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % mod;
            }
        }
    }
}

// Using combinatorics
#define MAX 100001
#define MOD 1000000007
int fact[MAX];
int ifact[MAX];

int power(int base, int exp, int mod) {
    if(exp == 0) return 1;
    int ret = power(base, exp / 2, mod) % mod;
    ret = 1LL * ret * ret % mod;
    if(exp & 1) {
        ret = 1LL * ret * base % mod;
    }
    return ret;
}

// Modular mutiplicative inverse
int modInv(int base, int mod = 1000000007) {
    return power(base, mod - 2, mod);
}

void init() {
    fact[0] = 1;
    ifact[0] = modInv(fact[0]);
    FOR(i, 1, MAX - 1) {
        fact[i] = 1LL * i * fact[i - 1] % MOD;
        ifact[i] = modInv(fact[i]);
    }
}

int ncr(int n, int r) {
    if(r > n) return 0;
    int ans = fact[n];
    ans = 1LL * ans * ifact[r] % MOD;
    ans = 1LL * ans * ifact[n - r] % MOD;
    return ans;
}