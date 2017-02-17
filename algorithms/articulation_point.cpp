//  low[u] be the earliest discovery time of any vertex in the subtree rooted at u or connected to a vertex in that subtree by a back edge.
vector <int> adj[MAX];
int low[MAX], disc[MAX], parent[MAX], dfstime, cnt = 0, N;
bool ap[MAX], visited[MAX];
 
void dfs(int u) {
    int children = 0;
    visited[u] = true;
    disc[u] = low[u] = ++dfstime;
 
    // If some child v of u has low[v] >= disc_time[u], then u is an articulation point.
    // low[u] = min( {low[v] | v is a child of u} and {disc_time[x] | (u, x) is a back edge from u or any child-vertex of it} )
 
    for(int i = 0; i < (int)adj[u].size(); i++) {
        int v = adj[u][i];
 
        if(!visited[v]) {
            ++children;
            parent[v] = u;
            dfs(v);
            // Check if the subtree rooted with v has a connection to
            // one of the ancestors of u
            low[u] = min(low[u], low[v]);
 
            // u is an articulation point in following cases
 
            // (1) u is root of DFS tree and has two or more children.
            if (parent[u] == -1 and children > 1)
                ap[u] = true;
 
            // (2) If u is not root and low value of one of its child is more
            // than discovery value of u.
            if (parent[u] != -1 and low[v] >= disc[u])
                ap[u] = true;
 
        } else if(v != parent[u]) // Update low value of u for parent function calls.
            low[u]  = min(low[u], disc[v]);
    }
 
}
 
void tarjanAP() {
    memset(ap, false, sizeof ap);
    memset(visited, false, sizeof visited);
    memset(parent, -1, sizeof parent);
    dfstime = 0, cnt = 0;
 
    for(int i = 1; i <= N; ++i) if(!visited[i]) dfs(i);
 
    for(int i = 1; i <= N; ++i) if(ap[i]) printf("%d ", i), ++cnt;
}