// How does this work? See http://www.geeksforgeeks.org/strongly-connected-components/
 
#define Max 105
vector <int> adj[Max], adj2[Max];
bool visited[Max];
int N;
 
stack <int> Stack;
 
void dfs1(int u) {
    visited[u] = true;
    for(int i = 0, n = (int)adj[u].size(); i < n; ++i) {
        int v = adj[u][i];
        if(!visited[v])
            dfs1(v);
    }
    Stack.push(u);
}
 
void transposeGraph() {
    for(int u = 0; u < N; ++u) {
        for(int i = 0, n = (int)adj[u].size(); i < n; ++i) {
            int v = adj[u][i];
            adj2[v].pb(u);
        }
    }
}
 
void dfs2(int u) {
    visited[u] = true;
    // printf("%d ", u);
    for(int i = 0, n = (int)adj2[u].size(); i < n; ++i) {
        int v = adj2[u][i];
        if(!visited[v])
            dfs2(v);
    }
}
 
void kosarajuSCC() {
    memset(visited, false, sizeof visited);
    for(int i = 0; i < N; ++i) if(!visited[i]) dfs1(i);
    transposeGraph();
    memset(visited, false, sizeof visited);
    while(!Stack.empty()) {
        int v = Stack.top();
        Stack.pop();
        if(!visited[v]) {
            dfs2(v);
            // printf("\n");
        }
    }
}