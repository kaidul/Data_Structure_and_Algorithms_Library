#define pii pair<int, int>
#define INF (1 << 30)
#define MAX 100001
vector <pii> node[MAX];
int dis[MAX + 1];
int vertex_no;
vector < pair<int, int> > node[MAX + 1];

// Time Complexity: O(V * E)
int bellman_ford(int src) {
    fill_n(dis, MAX, INF);
    dis[src] = 0;
    // relaxing E edges V - 1 times exactly
    for(int k = 0; k < vertex_no - 1; ++k) // O(V)
        for(int u = 0; u < vertex_no; ++u) for(int i = 0; i < (int)node[u].size(); ++i) { // O(E)
            int v = node[u][i].first, cost = node[u][i].second;
            dis[v] = min(dis[v], dis[u] + cost);
        }
    // rep(i, vertex_no) print(dis[i]);
}

// check whether a graph has any negative cycle
bool has_negative_cycle(int src) {
    bellman_ford(src);
    for(int u = 0; u < vertex_no; ++u) for(int i = 0; i < (int)node[u].size(); ++i) {
        int v = node[u][i].first, cost = node[u][i].second;
        if(dis[v] > dis[u] + cost)
            return true;
    }
    return false;
}