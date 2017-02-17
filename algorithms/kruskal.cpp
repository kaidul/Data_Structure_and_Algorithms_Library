#define MAX 100001
struct kruskal {
    int u, v, cost;
    kruskal() {}
    kruskal(int a, int b, int c): u(a), v(b), cost(c) {
    }
    bool operator < (const kruskal& other) const {
        return cost < other.cost;
    }
} g[MAX];

// Union-find Disjoint-Set Utility Functions
vector <int> pset;
void initSet(int _size) {
    pset.resize(_size);
    for(int i = 0; i < _size; ++i) pset[i] = i;
}
int findSet(int i) {
    return (pset[i] == i) ? i : (pset[i] = findSet(pset[i]));
}
void unionSet(int i, int j) {
    pset[findSet(i)] = findSet(j);
}
bool isSameSet(int i, int j) {
    return findSet(i) == findSet(j);
}

int mst(int edgeN, int vertexN) {
    int sum = 0, a, b, c;
    for(int i = 0; i < edgeN; i++) {
        scanf("%d %d %d", &a, &b, &c);
        g[i] = kruskal(a, b, c);
    }
    initSet(vertexN + 1);
    sort(g, g + edgeN);
    for(int i = 0; i < edgeN; ++i) {
        if(!isSameSet(g[i].u, g[i].v)) {
            sum += g[i].cost;
            unionSet(g[i].u, g[i].v);
        }
    }
    return sum;
}