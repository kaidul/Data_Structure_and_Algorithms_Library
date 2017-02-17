/**
 * generalized for Range maximum/minimum/sum query
 * Operation #1: Build Segment Tree upon an given array
 * Operation #2: Update the element of given index with value val
 * Operation #3: Query max/min/sum element within range [i, j]
 */
#include <cmath>
#include <iostream>
#include <vector>
 
using namespace std;
 
// code for three types of operation
enum RequestCode {rangeSum, rangeMin, rangeMax};
 
vector <int> segment_tree; // will contain the node value of ST
 
// array of data upon which we will build segment tree
int data[] = {21, 2, 7, 3, 4, 5, 1, 6, 9, 32, 11, 13, 23, 17, 8};
size_t arrLength = sizeof data / sizeof(data[0]); // size of the array
 
/**
 * allocate & initialize segment tree
 */
void initSegmentTree() {
    // the required segment tree array length is 2*2^(floor(log2(N))) + 1;
    int length = 2 * pow(2.0, floor(log((double) arrLength ) / log(2.0)) + 1 );
    segment_tree.clear();
    segment_tree.resize(length, 0);
}
 
/**
 * Time: O(n*log(n))
 * functions for building segment tree
 * buildHelper(code, node, begin, end)
 * buildSegmentTree(code)
 */
void buildHelper( RequestCode code, int node, int begin, int end ) {
    if (begin == end) {
        if (code == rangeSum) segment_tree[node] = data[begin];
        else segment_tree[node] = begin;
        return;
    }
    int leftIndx = node << 1, rightIndx = leftIndx | 1;
 
    buildHelper(code, leftIndx, begin, (begin + end) / 2);
    buildHelper(code, rightIndx, (begin + end) / 2 + 1, end);
 
    int lContent = segment_tree[leftIndx], rContent = segment_tree[rightIndx];
 
    if(code == rangeSum) segment_tree[node] = lContent + rContent;
    if(code == rangeMin) segment_tree[node] = ( data[lContent] <= data[rContent] ) ? lContent : rContent;
    if(code == rangeMax) segment_tree[node] = ( data[lContent] >= data[rContent] ) ? lContent : rContent;
 
}
 
void buildSegmentTree(RequestCode code) {
    buildHelper(code, 1, 0, arrLength - 1);
}
 
/**
 * Time: O(log(n))
 * query functions for ST
 * queryHelper(code, node, begin, end, lowerRange, upperRange)
 * query(code, loweRange, upperRange)
 */
//divide & conquer fashion [r1,r2] = [r1, (r1+r2)/2] , [(r1+r2)/2 + 1, r2]
int queryHelper(RequestCode code, int node, int begin, int end, int i, int j) {
    // if the current interval does not intersect query interval
    if (i > end || j < begin) return -1;
 
    if (begin >= i && end <= j) return segment_tree[node];
 
    // compute the minimum position in the left and right part of the interval
    int leftIndx = node << 1, rightIndx = leftIndx | 1;
    int pos1 = queryHelper(code, leftIndx, begin, (begin + end) / 2, i, j);
    int pos2 = queryHelper(code, rightIndx, (begin + end) / 2 + 1, end, i, j);
 
    // return the position where the overall minimum is
    if(pos1 == -1) return pos2; // can happen if we try to access segment outside query
    if(pos2 == -1) return pos1;
 
    if (code == rangeSum) {
        return pos1 + pos2;
    } else if(code == rangeMin) {
        return (data[pos1] <= data[pos2]) ? pos1 : pos2;
    } else return (data[pos1] >= data[pos2]) ? pos1 : pos2;
}
 
int query(RequestCode code, int lower, int upper) {
    return queryHelper(code, 1, 0, arrLength - 1, lower, upper);
}
 
/**
 * Time: O(log(n))
 * update functions for segment tree
 * updates an index with given value
 * updateHelper(code, begin, end, index, value)
 * update(code, index, value)
 */
/* root to leaf */
void updateHelper(RequestCode code, int node, int begin, int end, int index, int value ) {
 
    // this is the only condition and change that makes this updateHelper() function different from buildHelper()
    if( index < begin || index > end || begin > end ) return;
 
    if( begin == end ) {
        data[begin] = value; // data array is needed to be updated
 
        // rest of the code is same as buildHelper() method
        if(code == rangeSum) segment_tree[node] = data[begin];
        else segment_tree[node] = begin;
        return;
    }
    int leftIndx = node << 1, rightIndx = leftIndx | 1;
 
    updateHelper(code, leftIndx, begin, ( begin + end ) >> 1, index, value );
    updateHelper(code, rightIndx, ( ( begin + end ) >> 1 ) + 1, end, index, value );
 
    int lContent = segment_tree[leftIndx], rContent = segment_tree[rightIndx];
 
    if(code == rangeSum) segment_tree[node] = lContent + rContent;
    else if(code == rangeMin) segment_tree[node] = ( data[lContent] <= data[rContent] ) ? lContent : rContent;
    else if(code == rangeMax) segment_tree[node] = ( data[lContent] >= data[rContent] ) ? lContent : rContent;
}
 
void update(RequestCode code, int index, int item) {
    updateHelper(code, 1, 0, arrLength - 1, index, item);
}
 
int main() {
    initSegmentTree();
 
    buildSegmentTree(rangeMin);
    // query command for Range Minimum query from 0 to 8
    cout << query(rangeMin, 0, 8) << "\n";
 
    // update index 6 with value 100
    update(rangeMin, 6, 100);
    cout << query(rangeMin, 0, 8) << "\n";
 
    buildSegmentTree(rangeMax);
    cout << query(rangeMax, 0, 8) << "\n";
 
    buildSegmentTree(rangeSum);
    cout << query(rangeSum, 0, 8);
    return 0;
}