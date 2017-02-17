/*
General case for any k
f(n, k) = ((f(n - 1, k) + k - 1) mod n) + 1, f(1, k) = 1 (when n = 1...8)
*/
int josephus(int n, int k) {
    if(n == 1) return 0;
    return (josephus(n - 1, k) + k) % n;
}
 
/*
When k = 2
Proof: wikipedia
2 * (n - 2^floor(log2n)) + 1
*/
int josephusfor2(int n) {
    return 2 * (n - pow(2, floor(log((double) n) / log(2.0)))) + 1;
}
 
/*
 another proof for k = 2
 source: wikipedia
 n = 1b1b2b3b4...bm (bit representaion), ans = b1b2b3b4...bm1 (shifting leftmost bit into rightmost)
*/
int josephusfor2_bit(int n) {
    n <<= 1;
    n |= 1;
    int bit = floor((double)log(n) / log(2.0));
    int var = (1 << bit);
    --var;
    n &= var;
    return n;
}