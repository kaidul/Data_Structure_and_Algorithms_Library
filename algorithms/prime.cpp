vector<int> primes;
vector<bool> marked;

void sieve(int n) {
    marked = vector<bool>(n + 1, false);
    int sqrtN = sqrt(n);
    for(int i = 3; i <= sqrtN; i += 2) {
        if(!marked[i]) {
            for(int j = i; j <= n; j += (i << 1)) {
                marked[j] = true;
            }
            marked[i] = false;
        }
    }
    if(n >= 2) primes.push_back(2);
    for(int i = 3; i <= n; i += 2) {
        if(!marked[i]) {
            primes.push_back(i);
        }
    }
}

/***
calculate primes between L and R where 1 <= L <= R <= INT_MAX and 0 <= R - L <= 10^5
1. generate primes using sieve upto sqrt(INT_MAX)
2. using those primes calculate segmented sieve/primes between ranges
***/
void segmentedSieve(unsigned int left, unsigned int right) {
    int sqrtR = sqrt(right);
    marked = vector<bool>(right - left + 1, false); // marked.resize(right - left + 1, false) don't work :(
    
    for(int i = 1; i < primes.size() and primes[i] <= sqrtR; i++) {
        // offset is equal or immediate larger prime of left
        int offset = ((left + primes[i] - 1) / primes[i]) * primes[i];
        for(int j = offset; j <= right; j += primes[i]) {
            marked[j - left] = true;
        }
        if(offset == primes[i]) {
            marked[offset - left] = false;
        }
        
    }
    
    if(left <= 2 and 2 <= right) {
        // prime => 2
    }
    for(int i = max(((left & 1) ? left : left + 1), 3u); i <= right; i += 2) {
        if(!marked[i - left]) {
            // prime => i
        }
    }
}

// prime factorization using sieve
// 45 = 3^2 * 5^1
void primeFactor(int x, vector<pair<int, int>>& factors) {
    for(int i = 0; i < primes.size() and primes[i] <= x; i++) {
        if(x % primes[i] == 0) {
            int p = primes[i];
            int freq = 0;
            while(x % p == 0) {
                freq++;
                x /= p;
            }
            factors.push_back({p, freq});
        }
    }
}

// quick factorization without any preprocess
void primeFactor2(int x, vector<pair<int, int>>& factors) {
    int sqrtX = sqrt(x);
    if(x % 2 == 0) {
        int p = 2;
        int freq = 0;
        while(x % p == 0) {
            x /= p;
            freq++;
        }
        factors.push_back({p, freq});
    }
    for(int i = 3; i <= sqrtX; i += 2) {
        if(x % i == 0) {
            int p = i;
            int freq = 0;
            while(x % p == 0) {
                freq++;
                x /= p;
            }
            factors.push_back({p, freq});
        }
    }
}