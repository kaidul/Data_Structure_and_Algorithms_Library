#define CITY 3
#define INF (1 << 30)
bool visited [CITY] [1 << CITY]; // is_visited
int dp [CITY] [1 << CITY]; // cost at particular state
// path cost - weight[i][j] denotes cost for travel from city i to j
int weight [CITY] [CITY] = { {0, 2, 3},
    {19, 0, 6},
    {7, 8, 0}
};

int target = (1 << CITY) - 1;
int origin;

pair <int, int> trace[CITY][(1 << CITY) + 1];

bool Check(int N, int pos) {
    return (bool)(N & (1 << pos));
}

int Set(int N, int pos) {
    return N | (1 << pos);
}

int tspBitmask (int node, int mask) {
    if ( mask == target ) { // all visited
        visited [node] [mask] = true;
        trace[node][mask] = make_pair(origin, weight[node] [origin]);
        return dp [node] [mask] = weight[node] [origin];
    }
    
    if ( visited [node] [mask] )
        return dp [node] [mask];
    visited [node] [mask] = true;
    
    int ans = INF, v, cost;
    
    for ( int i = 0; i < CITY; i++ ) {
        if ( !Check(mask, i) ) {
            int ret = tspBitmask (i, Set(mask, i) );
            if (ret + weight [node][i] < ans) {
                ans = ret + weight [node][i];
                v = i;
                cost = weight[node][i];
            }
        }
    }
    trace[node][mask] = make_pair(v, cost);
    
    return dp [node] [mask] = ans;
}

void printPath() {
    memset (visited, false, sizeof visited);
    origin = 0;
    printf ("%d\n", tspBitmask (origin, (1 << origin) ));
    int mask = 0;
    mask |= (1 << origin);
    int u = origin, v, cost;
    for (int i = 0; i < CITY; i++) {
        v = trace[u][mask].first;
        cost = trace[u][mask].second;
        printf("%d %d %d\n", u, v, cost);
        mask |= (1 << v);
        u = v;
    }
}