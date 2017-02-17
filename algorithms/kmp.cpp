/*
The position of the text character compared can increase at most length(text)-1 times, the position of the first pattern character can increase at most length(text) - length(pattern) times, so the algorithm takes at most 2*length(text) - length(pattern) - 1 steps.
 
The preprocessing (construction of the border table) takes at most 2*length(pattern) steps, thus the overall complexity is O(m+n) and no more m + 2*n steps are executed if m is the length of the pattern and n the length of the text.
*/
void computeLPSArray(char *pat, int M, int *lps);
 
void KMPSearch(char *pat, char *txt) {
    int M = strlen(pat);
    int N = strlen(txt);
 
    // create lps[] that will hold the longest prefix suffix values for pattern
    int *lps = (int *) malloc(sizeof(int) * M);
    int j  = 0;  // index for pat[]
 
    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);
 
    int i = 0;  // index for txt[]
    while(i < N) {
        if(pat[j] == txt[i]) {
            j++;
            i++;
        }
 
        if (j == M) {
            printf("Found pattern at index %d \n", i - j);
            j = lps[j - 1];
        }
 
        // mismatch after j matches
        else if(pat[j] != txt[i]) {
            // Do not match lps[0..lps[j - 1]] characters,
            // they will match anyway
            if(j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    free(lps); // to avoid memory leak
}
 
void computeLPSArray(char *pat, int M, int *lps) {
    int len = 0;  // lenght of the previous longest prefix suffix
    int i;
 
    lps[0] = 0; // lps[0] is always 0
    i = 1;
 
    // the loop calculates lps[i] for i = 1 to M - 1
    while(i < M) {
        if(pat[i] == pat[len]) {
            lps[i++] = ++len;
        } else { // (pat[i] != pat[len])
            if( len != 0 ) {
                // This is tricky. Consider the example AAACAAAA and i = 7.
                len = lps[len - 1];
                // Also, note that we do not increment i here
            } else { // if (len == 0)
                lps[i++] = 0;
            }
        }
    }
}