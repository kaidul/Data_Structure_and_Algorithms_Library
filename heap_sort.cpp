/*
Details: Jane Alam Jan LightOj Tutorial
Usage:
heap Heap;
Heap.clear();
Heap.insert(value);
Heap.remove();
Heap.print();
*/
struct heap { // minHeap
    vector<int> data; // data to store the numbers as heap, 1 indexed
    int capacity;
    int n;  // the number of nodes in my array
    heap(int _size) { // constructor
        capacity = _size;
        data = vector<int>(capacity);
        clear(); // we clear the heap
    }
    void clear() { // initialize the heap
        n = 0; // initially there are no nodes in the heap
    }
    void insert( int K) { // inserting an element K in the heap
        if( n == capacity) { // the heap is full
            printf("cannot insert any more element, the heap is full\n");
            return;
        }
        ++n; // so, we have a new element, we increased n before adding
        // the element because we start from index 1
        data[n] = K; // inserted the element at the rightmost position
        int p = n; // for keeping the current position
        while( p > 1 ) { // p = 1 means we are on the root, and its a heap
            int pr = p / 2; // pr is the parent of p
            if( data[pr] > data[p] ) { // parent is greater than child
                swap( data[pr], data[p] );
                p = pr; // now the new position of the current element is pr
            } else break; // otherwise its a heap, so we can stop here
        }
    }
    int remove() { // removing the minimum element from the heap
        if( n == 0 ) { // is the heap is empty
            printf("The heap is empty, cannot delete.\n");
            return -1;
        }
        int K = data[1]; // first element in the heap is the minimum
        data[1] = data[n]; // brought the last element in 1st position
        n--; // as we removed one element, now we need to maintain the heap
 
        int p = 1; // as we moved the rightmost element in index 1
        while( 2 * p <= n ) { // means p has at least one child, if 2*p > n
            // we are sure that p is in the last level
            int ch = 2 * p; // contains the index of the child
            if( 2 * p + 1 <= n ) { // right child exists
                if( data[ch] > data[ch+1] ) // right child is smaller
                    // than left child
                    ch++; // ch contains the index of the right child
            }
            if( data[p] > data[ch] ) { // so, current node is larger
                // than its child
                swap( data[p], data[ch] );
                p = ch; // new position of the current element
            } else break; //current node is smaller than its children, so heap
        }
        return K; // as we stored the minimum element in K
    }
 
    void print() { // printing the heap
        printf("Number of elements: %d\n", n);
        for( int i = 1; i <= n; i++ ) printf("%d ", data[i]);
        printf("\n");
    }
 
    // Time: O(nlogn)
    // Extra space: O(1) as we will pass the input array as res here
    void heapSort(vector<int>& result) {
        for(int i = 0, len = n; i < len; ++i) {
            result[i] = remove();
        }
    }
};