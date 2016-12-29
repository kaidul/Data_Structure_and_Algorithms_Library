/*
Suffix array O(n lg^2 n)
LCP table O(n)
Explanation on how suffix array works: http://stackoverflow.com/a/17763563/1162233
*/
 
#define Max 1000
string S;
int N, gap;
int sa[Max]; // suffix array
// rank-lookup table(contains the lexicographic names)
// pos[k] contains the lexicographic name of the k-th m-gram of the previous step
int pos[Max];
// tmp[] is an auxiliary array used to help create pos[]
int tmp[Max];
int lcp[Max];
 
bool sufCmp(int i, int j) {
    if (pos[i] != pos[j])
        return pos[i] < pos[j];
    i += gap;
    j += gap;
    return (i < N and j < N) ? pos[i] < pos[j] : i > j;
}
 
void buildSA() {
    N = S.length();
    /* This is a loop that initializes sa[] and pos[].
       For sa[] we assume the order the suffixes have
       in the given string. For pos[] we set the lexicographic
       rank of each 1-gram using the characters themselves.
       That makes sense, right? */
    rep(i, N) sa[i] = i, pos[i] = S[i];
 
    /* Gap is the length of the m-gram in each step, divided by 2.
       We start with 2-grams, so gap is 1 initially. It then increases
       to 2, 4, 8 and so on. */
    for (gap = 1;; gap *= 2) {
        /* We sort by (gap*2)-grams: */
        sort(sa, sa + N, sufCmp);
 
        /* We compute the lexicographic renaming(rank) of each m-gram
           that we have sorted above. Notice how the rank is computed
           by comparing each n-gram at position i with its
           neighbor at i+1. If they are identical, the comparison
           yields 0, so the rank does not increase. Otherwise the
           comparison yields 1, so the rank increases by 1. */
        rep(i, N - 1) tmp[i + 1] = tmp[i] + sufCmp(sa[i], sa[i + 1]);
 
        /* tmp contains the rank by position. Now we map this
           into pos, so that in the next step we can look it
           up per m-gram, rather than by position. */
        rep(i, N) pos[sa[i]] = tmp[i];
 
        /* If the largest lexicographic name generated is
           n-1, we are finished, because this means all
           m-grams must have been different. */
        if (tmp[N - 1] == N - 1) break;
    }
}
 
void buildLCP() {
    for (int i = 0, k = 0; i < N; ++i)
        if (pos[i] != N - 1) {
            for (int j = sa[pos[i] + 1]; S[i + k] == S[j + k];) ++k;
            lcp[pos[i]] = k;
            if(k) --k;
        }
}
/*
    Suffix Array O(nlogn)
    Source: Competitive Programming by Felix Halim
*/
 
#define MAX 10050
int RA[MAX], tempRA[MAX]; // rank array and temporary rank array
int SA[MAX], tempSA[MAX]; // suffix array and temporary suffix array
int C[MAX]; // for counting/radix sort
// Ph[i] stores the suffix index of the previous suffix of suffix SA[i] in suffix array order
// PLCP - permuted longest common prefix
int Phi[MAX], PLCP[MAX], LCP[MAX];
 
void suffix_sort(int n, int k) {
    mem(C, 0); // clear frequency table
 
    for (int i = 0; i < n; i++) // count the frequency of each rank
        C[i + k < n ? RA[i + k] : 0]++;
 
    int sum = 0, N = max(256, n); // upto 255 ASCII chars or length of n
    for (int i = 0; i < N; i++) {
        int t = C[i];
        C[i] = sum;
        sum += t;
    }
 
    for (int i = 0; i < n; i++) // shuffle the suffix array if necessary
        tempSA[C[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
 
    memcpy(SA, tempSA, n*sizeof(int)); // update the suffix array
}
 
void suffix_array(string &s) {
    int n = s.size();
 
    // initial rankings
    for (int i = 0; i < n; i++)
        RA[i] = s[i] - '$';
 
    // initial SA {0, 1, 2, ...... n - 1}
    for (int i = 0; i < n; i++)
        SA[i] = i;
 
    // repeat sorting process log n times
    for (int k = 1; k < n; k *= 2) {
        suffix_sort(n, k); // radix sort. sort based on the second item
        suffix_sort(n, 0); // then stable sort.
 
        int r = tempRA[SA[0]] = 0; // re-ranking. start from rank r = 0
        for (int i = 1; i < n; i++) { // compare adjacent suffixes
 
            // if same pair, then same rank r; otherwise increase r
            int s1 = SA[i], s2 = SA[i - 1];
            bool equal = true;
            equal &= RA[s1] == RA[s2];
            equal &= RA[s1 + k] == RA[s2 + k];
            tempRA[SA[i]] = equal ? r : ++r;
        }
 
        memcpy(RA, tempRA, n * sizeof tempRA[0]); // update the rank array RA
    }
}
 
void Lcp(string &s) {
    int n = s.size();
 
    Phi[SA[0]] = -1; // default value i.e. there is no previous suffix that preceed suffix SA[0]
    for (int i = 1; i < n; i++) // compute Phi in O(n)
        Phi[SA[i]] = SA[i - 1]; // remember which suffix is behind this suffix
 
    for (int i = 0, L = 0; i < n; i++) { // compute permutated LCP in O(n)
        if (Phi[i] == -1) { // special case
            PLCP[i] = 0;
            continue;
        }
        // L will be increased max n times
        while (s[i + L] == s[Phi[i] + L])
            L++;
 
        PLCP[i] = L;
        // At least (L - 1) characters can match as the next suffix in position order will have one less starting
        // character than the current suffix. L will be decreased max n times
        L = max(L - 1, 0);
    }
 
    for (int i = 1; i < n; i++) // compute LCP in O(n)
        LCP[i] = PLCP[SA[i]]; // put the permutate LCP back to the correct position
}
 
int main(void) {
    cin >> S;
    S += '$';
    pf("O(n logn^2)\n");
    buildSA();
    buildLCP();
    rep(i, N - 1) print(sa[i]), println(lcp[i]);
    pf("O(nlogn)\n");
    suffix_array(S);
    Lcp(S);
    rep(i, N - 1) print(SA[i]), println(LCP[i + 1]);
    return 0;
}