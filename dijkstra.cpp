#define pii pair<int, int>
#define INF (1 << 30)
class Compare {
public:
    int operator() ( const pii& p1, const pii& p2 ) {
        return p1.second > p2.second;
    }
    
};

#define MAX 100001

priority_queue <pair<int, int>, vector<pair<int, int> >, Compare> q;
vector < pair<int, int> > adj[MAX + 1];
int dis[MAX + 1];
int N;

void reset() {
    q = priority_queue <pair<int, int>, vector< pair<int, int> >, Compare> ();
    for(int i = 0; i < MAX; ++i) {
        dis[i] = INF;
    }
}

int dijkstra(int &src, int &des) {
    reset();
    dis[src] = 0;
    q.push({src, dis[src]});
    while(!q.empty()) {
        int u = q.top().first;
        q.pop();
        if(u == des) return dis[des];
        for(int i = 0, n = (int)adj[u].size(); i < n; ++i) {
            int v = adj[u][i].first;
            int cost = adj[u][i].second;
            
            if(dis[v] > dis[u] + cost) {
                dis[v] = dis[u] + cost;
                q.push({v, dis[v]});
            }
        }
    }
    return -1;
}