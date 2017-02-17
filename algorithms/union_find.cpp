vector <int> pset, Rank;

void initSet(int _size) {
    pset.resize(_size);
    Rank.resize(_size);
    for(int i = 0; i < _size; ++i) {
        pset[i] = i;
        Rank[i] = i;
    }
}

int findSet(int u) {
    return (pset[u] == u) ? u : (pset[u] = findSet(pset[u])); // path compression
}

void unionSet(int u, int v) {
    int Pu = findSet(u), Pv = findSet(v);
    if(Pu == Pv) return;
    
    if(Rank[Pu] > Rank[Pv])
        pset[Pv] = Pu;
    else {
        pset[Pu] = Pv;
    }
    if(Rank[Pu] == Rank[Pv]) {
        Rank[Pv]++;
    }
}

bool isSameSet(int u, int v) {
    return findSet(u) == findSet(v);
}