template <class T>
class _2DBIT {
public:
    T** tree;
    int MaxX, MaxY;
 
    _2DBIT(int M, int N) {
        *tree = new T*[M + 1];
        for(int i = 0; i <= M; ++i)
            tree[i] = new T[N + 1];
        memset(tree, 0, sizeof(T) * (M + 1) * (N + 1));
        MaxX = M, MaxY = N;
    }
    ~_2DBIT() {
        free(tree);
    }
 
    void update(int x, int y, T val) {
        assert(x > 0 and y > 0);
        int y1;
        while(x <= MaxX) {
            y1 = y;
            while(y1 <= MaxY) {
                tree[x][y1] += val;
                y1 += (y1 & -y1);
            }
            x += (x & -x);
        }
    }
 
    T read(int x, int y) {
        assert(x > 0 and y > 0);
        int sum = 0, y1;
        while(x > 0) {
            y1 = y;
            while(y1 > 0) {
                sum += tree[x][y1];
                y1 -= (y1 & -y1);
            }
            x -= (x & -x);
        }
        return sum;
    }
};