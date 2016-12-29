// LCA without sparse table
int lca(int u, int v) {
    if(depth[u] > depth[v]) {
        swap(u, v);
    }
    while(depth[v] > depth[u]) {
        v = parent[v];
    }
    // assert(depth[v] == depth[u]);
    while(u != v) {
        u = parent[u], v = parent[v];
    }
    // assert(u == v);
    
    return u;
}

//LCA using sparse table
//Complexity: O(NlgN, lgN)
#define Max 100005
int depth[Max];
int table[Max][22]; // sparse table. there will be n rows for n nodes and logn columns for every node. pre-processing complexity O(nlogn) and Query complexity logn. table[i][j] holds 2^j th parent of ith node.
int parent[Max];
vector <int> adj[Max];
void dfs(int from, int u, int dep) {
    parent[u] = from;
    depth[u] = dep;
    for(int i = 0; i < (int)adj[u].size(); i++) {
        int v = adj[u][i];
        if(v == from) continue;
        dfs(u, v, dep + 1);
    }
}

void lcaInit(int N) {
    memset(table, -1, sizeof table);
    for(int i = 0; i < N; i++) {
        table[i][0] = parent[i];
    }
    
    for (int j = 1; (1 << j) < N; j++) {
        for(int i = 0; i < N; i++) {
            if (table[i][j - 1] != -1) {
                table[i][j] = table[table[i][j - 1]][j - 1];
            }
        }
    }
}

int lcaQuery(int p, int q) {
    if(depth[p] < depth[q]) {
        swap(p, q);
    }
    
    // building log's value
    int log = 1;
    while(true) {
        int next = log + 1;
        if((1 << next) > depth[p]) break;
        log++;
    }
    
    // uplifting p at the same level of q
    for(int i = log; i >= 0; i--) {
        if (depth[p] - (1 << i) >= depth[q]) {
            p = table[p][i];
        }
    }
    
    if (p == q) return p;
    
    // uplifting p and q untill both of their parents are same and we're in root
    for(int i = log; i >= 0; i--) {
        if (table[p][i] != -1 and table[p][i] != table[q][i]) {
            p = table[p][i];
            q = table[q][i];
        }
    }
    
    // when p and q are in the same level, return one of their parent
    return parent[p];
}
/*
 dfs(0, 0, 0);
 lcaInit(n);
 println(lcaQuery(u, v));
*/