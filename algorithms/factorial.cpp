int fact[MAX];
int invFact[MAX];

// nCr = n!/(n - r)! * r! => fact[n] * invFact[r] * invFact[n - r] % mod
void calcFact(int n, int Mod = 1000000007) {
    fact[0] = 1;
    for(int i = 1; i <= n; i++) {
        fact[i] = i * fact[i - 1] % mod;
        invFact[i] = modInv(fact[i], mod);
    }
}