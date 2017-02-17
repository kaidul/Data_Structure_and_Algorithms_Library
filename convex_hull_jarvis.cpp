/*
 Time Complexity: Theta(m * n)
 where n is number of input points and m is number of output or hull points (m <= n).
 Worst case: O(n^2)
 **** geometry template required ****
 */
#define MAX 100001

PointI points[MAX];
int N; // # of points
void convexHull() {
    // there must be atleast 3 points
    assert(N >= 3);
    
    // Initialize Result
    int next[N];
    fill(next, next + N, -1);
    
    // Find the leftmost point
    int l = 0;
    for (int i = 1; i < N; i++)
        if(cmp(points[i], points[l]))
            l = i;
    
    // Start from leftmost point, keep moving counterclockwise
    // until reach the start point again
    int p = l, q;
    do {
        // Search for a point 'q' such that orientation(p, q, i) is
        // counterclockwise for all points 'i'
        q = (p + 1) % N;
        for(int i = 0; i < N; i++) {
            if (ccw(points[p], points[q], points[i]) == -1) {
                q = i;
            }
        }
        
        next[p] = q;  // Add q to result as a next point of p
        p = q; // Set p as q for next iteration
    } while (p != l);
    
    // Print Result
    for(int i = 0; i < N; i++) {
        if (next[i] != -1) {
            cout << points[i] << endl;
        }
    }
}