/*
Source: Zobayer Blog
M > N and should be close, better both be primes.
M should be as much large as possible, not exceeding array size.
HKEY is the Hash function, change it if necessary.
*/
 
#define NIL -1
#define M 1021
#define N 1019
#define HKEY(x, i) ((x) % M + (i) * (1 + (x) % N)) % M
 
int a[M + 1];
 
inline int hash(int key) {
    int i = 0, j;
    do {
        j = HKEY(key, i);
        if(a[j] == NIL) { a[j] = key; return j; }
        i++;
    } while(i < M);
    return -1;
}
 
// key is encoded string(e.g. abc => 012, xyz => 232425) 
inline int find(int key) {
    int i = 0, j;
    do {
        j = HKEY(key, i);
        if(a[j] == key) return j;
        i++;
    } while(a[j] != NIL and i < M);
    return -1;
}