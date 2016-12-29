// average time: O(n + m), worst case: O(n * m)
// popular application: plagarism check

// d is the number of characters in input alphabet
#define d 256

void rkSearch(string const& pattern, string const& text) {
    int m = (int)pattern.length();
    int n = (int)text.length();

    int q = 101; // some small prime, must be less than INT_MAX

    int h = 1;
    // h = pow(d, M - 1) % q
    for(int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    // calculate the hash value of pattern and first window of text
    int pHash = 0;
    int tHash = 0;
    for(int i = 0; i < m; i++) {
        pHash = (d * pHash + pattern[i]) % q;
        tHash = (d * tHash + text[i]) % q;
    }

    // slide the pattern over text one by one
    for(int i = 0; i <= n - m; i++) {

        // check the hash value of current window of text and pattern
        // If the hash values match then only check for characters one by one
        if(pHash == tHash) {
            int j;
            for(j = 0; j < m; j++) {
                if(text[i + j] != pattern[j]) {
                    break;
                }
            }
            if(j == m) {
                // pattern found at index position i
            }
        }

        // calculate hash value of next window of text
        // remove leading digit, add trailing digit
        if(i < n - m) {
            tHash = (d * (tHash - text[i] * h) + text[i + m]) % q;

            // incase of getting negative value of tHash after modulo operation
            if(tHash < 0) {
                tHash += q;
            }
        }
    }
}