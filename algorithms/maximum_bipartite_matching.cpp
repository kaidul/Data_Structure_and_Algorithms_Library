// Maximum Bipartite matching using Edmond Karp maximum flow problem
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
        residual[u].resize(n);
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

/*
 There are M job applicants and N jobs. Each applicant has a subset of jobs that he/she is interested in.
 Each job opening can only accept one applicant and a job applicant can be appointed for only one job.
 Find an assignment of jobs to applicants in such that as many applicants as possible get jobs.
 */
// Create a flow network before where there is an edge with capacity 1 from each applicants to
// to each of his/her preferred jobs
// i.e. adj[i].push_back({j, 1})
int maxBPM(int N, int M) {
    // create two new nodes 'src' and 'sink'
    int src = N + M;
    int sink = N + M + 1;
    
    // total nodes = total nodes of bipartite graph + two extra nodes(source and sink)
    n = N + M + 2;
    
    // add edge with capacity of 1 unit from src to each applicants node
    for(int i = 0; i < N; i++) {
        adj[src].push_back({i, 1});
    }
    
    // add edge with capacity of 1 unit from each jobs node to sink
    for(int i = N; i < N + M; i++) {
        adj[i].push_back({sink, 1});
    }
    
    // Now the maximum flow from src to sink is the maximum matching of bipartite graph
    return edmondKarp(src, sink);
}