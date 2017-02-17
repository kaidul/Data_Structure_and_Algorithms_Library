/*
 Usage:
 i.e.
 f(n) = f(n - 1) + f(n - 2) for n > 1
      = a              for n = 0
      = b              for n = 1
 
 __        __     __      __  ^ (n - 1)    __
 |   f(n)     |   |  1   1   |             | b |
 |            | = |          |           * |   |
 | f(n - 1)   |   |  1   0   |             | a |
 |__        __|   |__      __|             |__ |
 
 code:
 matrix mat;
 mat.row = mat.col = 2;
 mat.v[0][0] = mat.v[0][1] = mat.v[1][0] = 1;
 mat.v[1][1] = 0;
 if (n < 3) {
    if (n == 0) println(a);
    if (n == 1) println(b);
    if (n == 2) println(a + b);
 } else {
    mat = power(mat, n - 1);
    int ans = b * mat.v[0][0] + a * mat.v[0][1];
    println(ans);
 }
 */

struct matrix {
    int v[Max][Max];
    int row, col;
};

matrix multiply(matrix &a, matrix &b) {
    assert(a.col == b.row);
    matrix r;
    r.row = a.row;
    r.col = b.col;
    rep(i, r.row) {
        rep(j, r.col) {
            int sum = 0;
            rep(k, a.col) {
                sum += a.v[i][k] * b.v[k][j];
                sum %= Mod;
            }
            r.v[i][j] = sum;
        }
    }
    return r;
}

/*
 // possibility of stack overflow
 matrix power(matrix mat, int p) {
    assert(p >= 1);
    if (p == 1) return mat;
    if (p % 2 == 1)
        return multiply(mat, power(mat, p - 1));
    matrix ret = power(mat, p / 2);
    ret = multiply(ret, ret);
    return ret;
 }
 */

void binary(int p, string &ret) {
    while (p > 0) {
        ret += (p % 2 == 0) ? "0" : "1";
        p /= 2;
    }
    reverse(ret.begin(), ret.end());
}

matrix power(matrix mat, int p) {
    string bin;
    binary(p, bin);
    matrix ret = mat;
    for (int i = 1; i < bin.size(); i++) {
        ret = multiply(ret, ret);
        if (bin[i] == '1') {
            ret = multiply(ret, mat);
        }
    }
    return ret;
}