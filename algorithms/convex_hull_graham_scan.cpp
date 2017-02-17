/*
 Time Complexity: O(n) + O(nLogn) + O(n)
 **** geometry template required ****
 */
#define MAX 100001

PointI points[MAX];
int N; // # of points

// A globle point needed for  sorting points with reference to the first point
// Used in compare function of qsort()
PointI p0;

// A utility function to find next to top in a stack
PointI nextToTop(stack<PointI> &S) {
    PointI p = S.top();
    S.pop();
    PointI res = S.top();
    S.push(p);
    return res;
}

// A function used by library function qsort() to sort an array of
// points with respect to the first point
int compare(const void *vp1, const void *vp2) {
    PointI *p1 = (PointI *)vp1;
    PointI *p2 = (PointI *)vp2;
    
    int side = getSide(p0, *p2, *p1);
    if (side == 0)
        return (dist(p0, *p2) >= dist(p0, *p1)) ? -1 : 1;
    
    return side;
}

// Prints convex hull of a set of n points.
void convexHull() {
    // Find the bottommost point
    int Min = 0;
    for (int i = 1; i < N; i++) {
        // Pick the bottom-most or chose the left most point in case of tie
        if (cmpYX(points[i], points[Min]))
            Min = i;
    }
    
    // Place the bottom-most point at first position
    swap(points[0], points[Min]);
    
    // Sort N - 1 points with respect to the first point.  A point p1 comes
    // before p2 in sorted ouput if p2 has larger polar angle (in
    // counterclockwise direction) than p1
    p0 = points[0];
    qsort(&points[1], N - 1, sizeof(PointI), compare);
    
    // Create an empty stack and push first three points to it.
    stack<PointI> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);
    
    // Process remaining n-3 points
    for (int i = 3; i < N; i++) {
        // Keep removing top while the angle formed by points next-to-top,
        // top, and points[i] makes a non-left turn
        while (getSide(nextToTop(S), points[i], S.top()) != -1)
            S.pop();
        S.push(points[i]);
    }
    
    // Now stack has the output points, print contents of stack
    while (!S.empty()) {
        PointI p = S.top();
        cout << p << endl;
        S.pop();
    }
}