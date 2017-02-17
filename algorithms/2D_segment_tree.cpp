/*
Usage:
Segtree2d TMax;
Segtree2dMin TMin;
TMax.clear(Row, Col);
TMax.update(x, y, value);
TMax.query(x1, y1, x2, y2);
 */
int P[Max][Max];
 
struct Point {
    int x, y, mx;
    Point() {}
    Point(int x, int y, int mx) : x(x), y(y), mx(mx) { }
 
    bool operator < (const Point& other) const {
        return mx < other.mx;
    }
};
 
struct Segtree2d {
    Point T[2 * Max * Max]; // assumed, not accurate
    int n, m;
 
    void clear(int n, int m) {
        this -> n = n;
        this -> m = m;
        build(1, 1, 1, n, m);
    }
 
    Point build(int node, int a1, int b1, int a2, int b2) {
        if (a1 > a2 or b1 > b2)
            return def();
 
        if (a1 == a2 and b1 == b2)
            return T[node] = Point(a1, b1, P[a1][b1]);
 
        T[node] = def();
        T[node] = maxNode(T[node], build(4 * node - 2, a1, b1, (a1 + a2) / 2, (b1 + b2) / 2 ) );
        T[node] = maxNode(T[node], build(4 * node - 1, (a1 + a2) / 2 + 1, b1, a2, (b1 + b2) / 2 ));
        T[node] = maxNode(T[node], build(4 * node + 0, a1, (b1 + b2) / 2 + 1, (a1 + a2) / 2, b2) );
        T[node] = maxNode(T[node], build(4 * node + 1, (a1 + a2) / 2 + 1, (b1 + b2) / 2 + 1, a2, b2) );
        return T[node];
    }
 
    Point query(int node, int a1, int b1, int a2, int b2, int x1, int y1, int x2, int y2) {
        if (x1 > a2 or y1 > b2 or x2 < a1 or y2 < b1 or a1 > a2 or b1 > b2)
            return def();
 
        if (x1 <= a1 and y1 <= b1 and a2 <= x2 and b2 <= y2)
            return T[node];
 
        Point mx = def();
        mx = maxNode(mx, query(4 * node - 2, a1, b1, (a1 + a2) / 2, (b1 + b2) / 2, x1, y1, x2, y2) );
        mx = maxNode(mx, query(4 * node - 1, (a1 + a2) / 2 + 1, b1, a2, (b1 + b2) / 2, x1, y1, x2, y2) );
        mx = maxNode(mx, query(4 * node + 0, a1, (b1 + b2) / 2 + 1, (a1 + a2) / 2, b2, x1, y1, x2, y2) );
        mx = maxNode(mx, query(4 * node + 1, (a1 + a2) / 2 + 1, (b1 + b2) / 2 + 1, a2, b2, x1, y1, x2, y2));
 
        return mx;
    }
 
    Point query(int x1, int y1, int x2, int y2) {
        return query(1, 1, 1, n, m, x1, y1, x2, y2);
    }
 
    Point update(int node, int a1, int b1, int a2, int b2, int x, int y, int value) {
        if (a1 > a2 or b1 > b2)
            return def();
 
        if (x > a2 or y > b2 or x < a1 or y < b1)
            return T[node];
 
        if (x == a1 and y == b1 and x == a2 and y == b2)
            return T[node] = Point(x, y, value);
 
        Point mx = def();
 
        mx = maxNode(mx, update(4 * node - 2, a1, b1, (a1 + a2) / 2, (b1 + b2) / 2, x, y, value) );
        mx = maxNode(mx, update(4 * node - 1, (a1 + a2) / 2 + 1, b1, a2, (b1 + b2) / 2, x, y, value));
        mx = maxNode(mx, update(4 * node + 0, a1, (b1 + b2) / 2 + 1, (a1 + a2) / 2, b2, x, y, value));
        mx = maxNode(mx, update(4 * node + 1, (a1 + a2) / 2 + 1, (b1 + b2) / 2 + 1, a2, b2, x, y, value) );
 
        return T[node] = mx;
    }
 
    Point update(int x, int y, int value) {
        return update(1, 1, 1, n, m, x, y, value);
    }
 
    // utility functions; these functions are virtual because they will be overridden in child class
    virtual Point maxNode(Point a, Point b) {
        return max(a, b);
    }
 
    virtual Point def() {
        return Point(0, 0, -INF);
    }
};
 
struct Segtree2dMin : Segtree2d {
    Point maxNode(Point a, Point b) {
        return min(a, b);
    }
 
    Point def() {
        return Point(0, 0, INF);
    }
};