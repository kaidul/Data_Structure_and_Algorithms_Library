//  low[u] be the earliest discovery time of any vertex in the subtree rooted at u or connected to a vertex in that subtree by a back edge.
int low[MAX], disc[MAX], parent[MAX], dfstime;
bool visited[MAX];
vector <Point> adj[MAX], result;
 
void dfs(int u) {
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
 
            // If the lowest vertex reachable from subtree under v is
            // below u in DFS tree, then u-v is a bridge
            if (low[v] > disc[u]) result.push_back(Point(u, v));
 
        } else if(v != parent[u]) // Update low value of u for parent function calls.
            low[u]  = min(low[u], disc[v]);
    }
 
}
 
void tarjanBridge() {
    memset(visited, false, sizeof visited);
    memset(parent, -1, sizeof parent);
    dfstime = 0;
    for(int i = 0; i < N; ++i) if(!visited[i]) tarjan(i);
}