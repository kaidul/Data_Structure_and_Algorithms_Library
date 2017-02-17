// Increase each value by x from segment s1 to s2
vector <int> segment_tree;
vector <int> propagation; // for lazy propagation
 
int data[] = {1, 2, 3, 4, 5, 6};
size_t arrLength = sizeof data / sizeof(data[0]);
 
 
void initSegmentTree() {
    // the required segment tree array length is 2*2^(floor(log2(N))) + 1;
    int length = 2 * pow(2.0, floor(log((double) arrLength ) / log(2.0)) + 1 );
    segment_tree.clear();
    segment_tree.resize(length, 0);
    propagation.clear();
    propagation.resize(length, 0);
}
 
 
void buildHelper(int node, int begin, int end ) {
    if (begin == end) {
        segment_tree[node] = data[begin];
        return;
    }
    int leftIndx = 2 * node, rightIndx = 2 * node + 1;
 
    buildHelper(leftIndx, begin, (begin + end) / 2);
    buildHelper(rightIndx, (begin + end) / 2 + 1, end);
 
    int lContent = segment_tree[leftIndx], rContent = segment_tree[rightIndx];
 
    segment_tree[node] = lContent + rContent;
 
}
 
void buildSegmentTree() {
    buildHelper(1, 0, arrLength - 1);
}
 
 
//[r1,r2] = [r1, (r1+r2)/2] , [(r1+r2)/2 + 1, r2]
int queryHelper(int node, int begin, int end, int i, int j) {
    // if the current interval does not intersect query interval
    if (i > end or j < begin) return -1;
 
    if (begin >= i and end <= j) return segment_tree[node];
 
    // compute the minimum position in the left and right part of the interval
    int pos1 = queryHelper(2 * node, begin, (begin + end) / 2, i, j);
    int pos2 = queryHelper(2 * node + 1, (begin + end) / 2 + 1, end, i, j);
 
    // return the position where the overall minimum is
    if(pos1 == -1) return pos2; // can happen if we try to access segment outside query
    if(pos2 == -1) return pos1;
 
    return pos1 + pos2;
}
 
int query(int lower, int upper) {
    return queryHelper(1, 0, arrLength - 1, lower, upper);
}
 
void lazyUpdateHelper(int node, int begin, int end, int i, int j, int value ) {
 
    // this is the only condition and change that makes this updateHelper() function different from buildHelper()
    if (i > end or j < begin) return;
 
    // node's range is inside the range to be updated
    if (begin >= i and end <= j) {
        propagation[node] += value;
        segment_tree[node] += (end - begin + 1) * value;
        return;
    }
 
    int leftIndx = node * 2, rightIndx = node * 2 + 1;
 
    lazyUpdateHelper(leftIndx, begin, ( begin + end ) / 2, i, j, value );
    lazyUpdateHelper(rightIndx, ( begin + end ) / 2 + 1, end, i, j, value );
 
    int lContent = segment_tree[leftIndx], rContent = segment_tree[rightIndx];
 
    segment_tree[node] = lContent + rContent + (end - begin + 1) * propagation[node];
}
 
void lazyUpdate(int lower, int upper, int item) {
    lazyUpdateHelper(1, 0, arrLength - 1, lower, upper, item);
}
 
int lazyQueryHelper(int node, int begin, int end, int i, int j, int carry = 0) {
    // if the current interval does not intersect query interval
    if (i > end or j < begin) return -1;
 
    if (begin >= i and end <= j) return segment_tree[node] + carry * (end- begin + 1);
 
    // compute the minimum position in the left and right part of the interval
    int pos1 = lazyQueryHelper(2 * node, begin, (begin + end) / 2, i, j, carry + propagation[node]);
    int pos2 = lazyQueryHelper(2 * node + 1, (begin + end) / 2 + 1, end, i, j, carry + propagation[node]);
 
    // return the position where the overall minimum is
    if(pos1 == -1) return pos2; // can happen if we try to access segment outside query
    if(pos2 == -1) return pos1;
 
    return pos1 + pos2;
}
 
int lazyQuery(int lower, int upper) {
    return lazyQueryHelper(1, 0, arrLength - 1, lower, upper, 0);
}