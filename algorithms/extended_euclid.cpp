/*
Extended Euclid
ax + by = gcd(a, b), find x and y
answer ex(25, 18) = ((-5, 7), 1) as (-5) * 25 + 18 * 7 = 1
*/
void ex_gcd(int a, int b, int &d, int &x, int &y) { // ax + by = d( gcd(a, b) )
    if(b == 0) {
        x = 1, y = 0, d = a;
        return;
    }
    int x1, y1;
    ex_gcd(b, a % b, d, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
}

/*
ax + by = c, find x and y
i.e. 25x + 18y = 839 -> x = 17, y = 23
*/
void diophantine(int a, int b, int &d, int &x, int &y) {
    ex_gcd(a, b, d, x, y);
    x *= n / d, y *= n / d;
    a /= d, b /= d;
    int c = ceil(-(double) x / b), f = ceil((double) y / a);
    if(c < f)
        x += b * c, y -= a * c;
    else
        x += b * f, y -= a * f;
}

// Modular mutiplicative inverse using extended euclid
// Time complexity: O(log(m)^2)
int modInv(int a, int mod, int &d, int &x, int &y) {
    ex_gcd(a, m, d, x, y);
    if(d > 1) return 0;
    int ret = x % m;
    return (ret < 0 ? ret + mod : ret);
}