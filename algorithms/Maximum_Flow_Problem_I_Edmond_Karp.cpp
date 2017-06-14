// Ford-Fulkerson + Edmond Karp algorithm
// single source - single sink maximum flow
#define MAX 1005

vector<pair<int, int>> adj[MAX]; // adj[u] = {{v1, capacity1}, {v2, capacity2}}
vector<int> residual[MAX]; // residual[u][v1] = capacity1
int parent[MAX];
bool visited[MAX];
int n;

/* Returns true if there is a path from 'src' to 'sink' in
 residual graph. Also fills parent[] to store the path */
bool bfs(int src, int sink) {
    memset(visited, false, sizeof visited);
    queue <int> q;
    q.push(src);
    visited[src] = true;
    parent[src] = -1;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for(int i = 0; i < (int)adj[u].size(); i++) {
            int v = adj[u][i].first;
            if(!visited[v] and residual[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    
    // If we reached sink in BFS starting from source, then return true, else false
    return visited[sink];
}

int edmondKarp(int src, int sink) {
    int maxFlow = 0;
    for(int u = 0; u < n; u++) {
        for(int i = 0; i < (int)adj[u].size(); i++) {
            int v = adj[u][i].first;
            int capacity = adj[u][i].second;
            residual[u][v] = capacity;
        }
    }
    while(bfs(src, sink)) {
        int pathFlow = INT_MAX;
        // trace augmenting path
        int v = sink;
        while(v != src) {
            int u = parent[v];
            pathFlow = min(pathFlow, residual[u][v]);
            v = u;
        }
        
        // update residual graph
        v = sink;
        while(v != src) {
            int u = parent[v];
            residual[u][v] -= pathFlow;
            residual[v][u] += pathFlow;
            v = u;
        }
        
        maxFlow += pathFlow;
    }
    
    return maxFlow;
}