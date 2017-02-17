// Intuition behind BIT: http://stackoverflow.com/a/15444954/1162233
template<class T>
class BIT {
public:
    T *tree;
    int MaxVal; // maximum value which will have non-zero frequency
 
    BIT(int N) {
        tree = new T[N + 1];
        memset(tree, 0, sizeof(T) * (N + 1));
        MaxVal = N;
    }
 
    ~BIT() {
        free(tree);
    }
 
    // O(MaxVal logMaxVal)
    void build(int* data) {
        for(int i = 1; i <= MaxVal; ++i) { // O(MaxVal)
            int idx = i;
            while(idx <= MaxVal) { // O(log MaxVal)
                tree[idx] += data[i];
                idx += (idx & -idx);
            }
        }
    }
 
    // Time: O(log maxVal)
    void update(int idx, T val) {
        assert(idx > 0);
        while (idx <= MaxVal) {
            tree[idx] += val;
            idx += (idx & -idx);
        }
    }
    //Returns the cumulative frequency of index idx
    // Time: O(log maxVal)
    T read(int idx) {
        assert(idx > 0);
        T sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }
 
    // Time: c * O(log maxVal); where c is a constant less than 1
    T readSingle(int idx) {
        assert(idx > 0);
        T sum = tree[idx];
        if(idx == 0) return sum;
         
        int z = idx - (idx & -idx);
        int y = idx - 1; // y is predeccesor of x
        while(y != z) {
            sum -= tree[y];
            y -= (y & -y);
        }
        return sum;
    }
 
    // Time: O(maxVal)
    void scale(T factor) {
        for(int i = 1; i <= MaxVal; ++i) {
            tree[i] /= factor; // scale-down
            // tree[i] *= factor; // scale-up
        }
    }
 
    // if in tree exists more than one index with a same
    // cumulative frequency, this procedure will return
    // some of them (we do not know which one)
 
    // bitMask - initialy, it is the greatest bit of MaxVal
    // bitMask store interval which should be searched
    int find(T cumFre) {
        int idx = 0; // this var is result of function
        int bitMask = (1 << (int) floor(log((double) MaxVal) / log(2.0)));
 
        while((bitMask != 0) and (idx < MaxVal)) { // nobody likes overflow :)
            int tIdx = idx + bitMask; // we make midpoint of interval
            if (cumFre == tree[tIdx]) // if it is equal, we just return idx
                return tIdx;
            else if (cumFre > tree[tIdx]) {
                // if tree frequency "can fit" into cumFre,
                // then include it
                idx = tIdx; // update index
                cumFre -= tree[tIdx]; // set frequency for next loop
            }
            bitMask >>= 1; // half current interval
        }
        if (cumFre != 0) // maybe given cumulative frequency doesn't exist
            return -1;
        else
            return idx;
    }
 
};