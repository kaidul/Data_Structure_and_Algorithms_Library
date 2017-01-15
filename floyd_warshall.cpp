#define MAX 1000
int dis[MAX][MAX];
int nxt[MAX][MAX];
int edges, vertices;
/*
 Time: O(n^3)
 Space: O(n^2)
 */
void floyd_warshall() {
    memset(dis, INF, sizeof dis);
    int u, v, cost;
    for(int i = 0; i < edges; ++i) scanf("%d %d %d", &u, &v, &cost), dis[u][v] = cost;
    // next[i][j] = k; path from i to j, k is the next node
    for(int i = 0; i < vertices; ++i) {
        for(int j = 0; j < vertices; ++j) {
            nxt[i][j] = j;
        }
    }
    
    for(int k = 0; k < vertices; ++k) {
        for(int i = 0; i < vertices; ++i) {
            for(int j = 0; j < vertices; ++j) {
                if(dis[i][k] + dis[k][j] < dis[i][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                    nxt[i][j] = nxt[i][k];
                }
            }
        }
    }
}

void findPath(int src, int dest, vector<int>& path) {
    path.push_back(src);
    int u = src;
    while(u != dest) {
        u = nxt[u][dest];
        path.push_back(u);
    }
}

// mini-max
/*
 for(int k = 0; k < vertices; ++k)
 for(int i = 0; i < vertices; ++i)
 for(int j = 0; j < vertices; ++j)
 dis[i][j] = min(dis[i][j], max(dis[i][k], dis[k][j]));
 */

// Transitive closure: if there is a direct/indirect path between i to j. input dis[u][v] = 1 if path else 0 (no need to assign cost)
/*
 for(int k = 0; k < vertices; ++k)
 for(int i = 0; i < vertices; ++i)
 for(int j = 0; j < vertices; ++j)
 dis[i][j] = dis[i][j] | (dis[i][k] & dis[k][j]);
 */