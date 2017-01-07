char arr[] = {'a','b','c','d'};
int N = sizeof(arr) / sizeof(arr[0]);
vector <char> result;
int mask = 0, maxN = (1 << N) - 1;

bool Check(int N, int pos) {
    return (bool)(N & (1 << pos));
}

int Set(int N, int pos) {
    return N | (1 << pos);
}

int Reset(int N, int pos) {
    return N & ~(1 << pos);
}

void bktk_bitmask() {
    if(mask == maxN) {
        for(int i = 0; i < N; i++)
            printf("%c", result[i]);
        putchar('\n');
        return;
    }
    for(int i = 0; i < N; i++) {
        if(!Check(mask, i) ) {
            mask = Set(mask, i);
            result.push_back( arr[i] );
            bktk_bitmask();
            mask = Reset(mask, i);
            result.pop_back();
        }
    }
}

bool taken[20] = {false};
void bktk() {
    if(result.size() == N) {
        for(int i = 0; i < N; i++)
            printf("%c", result[i]);
        putchar('\n');
        return;
    }
    for(int i = 0; i < N; i++) {
        if(taken[i] == false) {
            taken[i] = true;
            result.push_back( arr[i] );
            bktk();
            taken[i] = false;
            result.pop_back();
        }
    }
}

void permute() {
    do{
    } while(prev_permutation(arr, arr + N));
    do{
        // print permutation
    } while(next_permutation(arr, arr + N));
}

void permuteUtil(int indx) {
    if(indx == N) {
        for(int i = 0; i < N; i++) {
            printf("%c ", arr[i]);
        }
        printf("\n");
        return;
    }
    for(int i = indx; i < N; i++) {
        swap(arr[indx], arr[i]);
        permuteUtil(indx + 1);
        swap(arr[indx], arr[i]);
    }
}

void permute2() {
    return permuteUtil(0);
}