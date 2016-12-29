int powerUtil(int base, int exp, int mod) {
    if(exp == 0) return 1;
    int ret = powerUtil(base, exp / 2, mod) % mod;
    ret = 1LL * ret * ret % mod;
    if(exp & 1) {
        ret = 1LL * ret * base % mod;
    }
    return ret;
}

double power(int base, int exp, int mod = 1000000007) {
    if(exp < 0) {
        if(base == 0) return DBL_MAX; // undefined
        return 1 / (double) powerUtil(base, -exp, mod); // return type will be double/long double then
    }
    return powerUtil(base, exp, mod);
}

// Modular mutiplicative inverse
int modInv(int base, int mod = 1000000007) {
    return powerUtil(base, mod - 2, mod);
}