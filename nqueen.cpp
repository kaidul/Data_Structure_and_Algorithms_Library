int x[9];

bool isPlacable(int queen, int row) {
    for(int prev = 1; prev < queen; prev++) {
        if (x[prev] == row || abs(x[prev] - row) == abs(prev - queen) ) {
            return false;
        }
    }
    return true;
}

// nQueen(1);
void nQueen(int queen) {
    for(int row = 1; row <= 8; row++) {
        if (isPlacable(queen, row)) {
            x[queen] = row;
            // found a solution
            if (queen == 8) {
                for(int i = 1; i <= 8; i++) {
                    // print
                }
                return;
            }
            nQueen(queen + 1);
        }
        
    }
}