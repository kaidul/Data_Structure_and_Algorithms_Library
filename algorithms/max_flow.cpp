/*
 Time Complexity: O(V * E^2)
 */
#define MAX 100001
#define INF (1 << 30)
vector<int> adj[MAX];
bool visited[MAX];
int flow[MAX][MAX];
int par[MAX];
int src, dest;
int f;
void augmentPath(int v, int minEdge) {
    if(v == src) {
        f = minEdge;
        return;
    } else if(visited[v]) {
        augmentPath(par[v], min(minEdge, flow[par[v]][v]));
        // update residue network
        flow[par[v]][v] -= f; // main flow
        flow[v][par[v]] += f; // reverse flow
    }
}

int EdmonMaxFlow() {
    int maxFlow = 0;
    memset(par, 0, sizeof par);
    // run BFS from source to destination and construct a path until flow = 0
    while(true) { // O(V)
        f = 0;
        memset(visited, false, sizeof visited);
        queue< int > q;
        q.push(src), visited[src] = true;
        
        while(!q.empty()) { // O(E)
            int v, u = q.front(); q.pop();
            if(u == dest) break;
            
            for(int i = 0; i < (int)adj[u].size(); i++) {
                v = adj[u][i];
                if(!visited[v] and flow[u][v] > 0) {
                    visited[v] = true, par[v] = u;
                    q.push(v);
                }
            }
            
        }
        // O(E)
        augmentPath(dest, INF); // updating the residue network.
        if(f == 0) break; // flow zero so no new flow is possible
        maxFlow += f;
    }
    return maxFlow;
}
