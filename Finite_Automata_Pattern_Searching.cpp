#define NO_OF_CHARS 256
#define M 30 // number of characters in pattern
int m, n;
int TF[M][NO_OF_CHARS];

void computeTransFunc(string pattern) {
    for(int x = 0; x < NO_OF_CHARS; ++x) {
        TF[0][x] = 0;
    }
    TF[0][pattern[0]] = 1;

    for(int i = 1, LPS = 0; i <= m; ++i) {
        for(int x = 0; x < NO_OF_CHARS; ++x) {
            TF[i][x] = TF[LPS][x];
        }
        TF[i][pattern[i]] = i + 1;

        if(i < m) {
            LPS = TF[LPS][pattern[i]];
        }
    }
}

void search(string pattern, string txt) {
    m = pattern.length();
    n = txt.length();

    computeTransFunc(pattern);

    for(int i = 0, j = 0; i < n; ++i) {
        j = TF[j][txt[i]];
        if(j == m) {
            printf ("pattern found at index %d\n", i - m + 1);
        }
    }
}