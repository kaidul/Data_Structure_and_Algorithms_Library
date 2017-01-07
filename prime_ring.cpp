// prime ring where the sum of numbers in two adjacent circles should be a prime
int n;
int a [20];
bool available [20];
int isPrime [42] = {0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0,
                    1, 0, 1, 0, 0, 0, 1, 0, 1, 0,
                    0, 0, 1, 0, 0, 0, 0, 0, 1, 0,
                    1, 0, 0, 0, 0, 0, 1, 0, 0, 0,
                    1
                   };
 
bool valid (int indx, int ring) {
    if ( ring == n - 1 ) {
        if (isPrime [a [ring - 1] + indx] && isPrime [indx + 1])
            return true;
        return false;
    }
    return isPrime [a [ring - 1] + indx];
}
 
// bktk(1);
void bktk (int ring) {
    if ( ring == n ) {
        printf ("%d", a [0]);
        for ( int i = 1; i < n; i++ )
            printf (" %d", a [i]);
        printf ("\n");
        return;
    }
 
    for ( int i = 2; i <= n; i++ ) {
        if ( available [i] ) {
            if ( valid (i, ring) ) {
                available [i] = false;
                a [ring] = i;
                bktk (ring + 1);
                available [i] = true;
            }
        }
    }
}