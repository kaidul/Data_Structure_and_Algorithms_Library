#define MAX 100001

int dp[MAX << 2][2];
int parent[MAX];
vector <int> adj[MAX];

int minVertexCover(int node, bool hasGuard) {
    
    if( (int)adj[node].size() == 0 ) return 0;
    if( dp[node][hasGuard] != -1 ) return dp[node][hasGuard];
    
    int sum = 0;
    for(int i = 0; i < (int)adj[node].size(); i++) {
        int v = adj[node][i];
        if( v != parent[node] ) {
            parent[v] = node;
            if(!hasGuard) {
                sum += minVertexCover(v, true);
            } else {
                sum += min( minVertexCover(v, false), minVertexCover(v, true) );
            }
        }
    }
    return dp[node][hasGuard] = sum + hasGuard;
}

/*
usage:
result = min( minVertexCover(1, false), minVertexCover(1, true) );
if(n > 1) printf("%d\n", result);
else printf("1\n");
*/