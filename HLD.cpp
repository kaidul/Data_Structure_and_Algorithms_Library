/*
 problem ID: QTREE (spoj)
 source: Anudeep's blog on HLD
 Time Complexity: O(log^2 n)
 */
#define root 0
#define N 10100
#define LogN 14 // log(N)
#define segTreeSize 32768 // 2 * pow(2.0, floor(log((double) N ) / log(2.0)) + 1

vector <int> adj[N], costs[N], indexx[N];
int baseArray[N], ptr;
int chainNo, chainInd[N], chainHead[N], posInBase[N];
int depth[N], table[N][LogN], otherEnd[N], subTreeSize[N];
int segment_tree[segTreeSize];

// See Segment Tree for Implementation

void buildSegTree(int node = 1, int start = 0, int end = ptr - 1);

void update(int node, int start, int end, int index, int value );

int querySegTree(int node, int start, int end, int i, int j);

/*
 * query_up:
 * It takes two nodes u and v, condition is that v is an ancestor of u
 * We query the chain in which u is present till chain head, then move to next chain up
 * We do that way till u and v are in the same chain, we query for that part of chain and break
 */

int query_up(int u, int v) {
    if(u == v) return 0; // Trivial
    int uchain, vchain = chainInd[v], ans = -1, ret;
    // uchain and vchain are chain numbers of u and v
    while(true) {
        uchain = chainInd[u];
        if(uchain == vchain) {
            // Both u and v are in the same chain, so we need to query from u to v, update answer and break.
            // We break because we came from u up till v, we are done
            if(u == v) break;
            ret = querySegTree(1, 0, ptr - 1, posInBase[v] + 1, posInBase[u]);
            // Above is call to segment tree query function
            ans = max(ans, ret); // Update answer
            break;
        }
        ret = querySegTree(1, 0, ptr - 1, posInBase[chainHead[uchain]], posInBase[u]);
        // Above is call to segment tree query function. We do from chainHead of u till u. That is the whole chain from
        // start till head. We then update the answer
        ans = max(ans, ret);
        u = chainHead[uchain]; // move u to u's chainHead
        u = table[u][0]; //Then move to its parent, that means we changed chains
    }
    return ans;
}

// See LCA section

int lcaQuery(int u, int v);

void lcaInit(int n);

void query(int u, int v) {
    int lca = lcaQuery(u, v);
    int ans = max(query_up(v, lca), query_up(u, lca));
    printf("%d\n", ans);
}

void change(int i, int val) {
    int u = otherEnd[i];
    update(1, 0, ptr - 1, posInBase[u], val);
}

void HLD(int curNode = root, int cost = -1, int prev = -1) {
    if(chainHead[chainNo] == -1) { // Given a chain, what is the head of the chain
        chainHead[chainNo] = curNode; // Assign chain head
    }
    chainInd[curNode] = chainNo; // Given a node, to which chain does that node belong to
    //chainPos[cur] = chainSize[chainNo]; // Given a node, what is the position of that node in its chain
    //chainSize[chainNo]++; // Given a chain, what is the length of the chain
    posInBase[curNode] = ptr; // Position of this node in baseArray which we will use in Segtree
    baseArray[ptr++] = cost;
    
    int sc = -1, ncost;
    // Loop to find special child
    for(int i = 0, n = (int)adj[curNode].size(); i < n; i++) {
        int v = adj[curNode][i];
        if(v != prev) {
            if(sc == -1 or subTreeSize[sc] < subTreeSize[v]) {
                sc = v, ncost = costs[curNode][i];
            }
        }
    }
    
    if(sc != -1) { // Incase of curNode is leaf node
        // Expand the chain
        HLD(sc, ncost, curNode);
    }
    
    for(int i = 0, n = (int)adj[curNode].size(); i < n; i++) {
        int v = adj[curNode][i];
        if(v != prev and v != sc) {
            // New chains at each normal node
            chainNo++;
            HLD(v, costs[curNode][i], curNode);
        }
    }
}

void dfs(int cur = root, int prev = -1, int _depth = 0) {
    table[cur][0] = prev;
    depth[cur] = _depth;
    subTreeSize[cur] = 1;
    for(int i = 0, n = (int)adj[cur].size(); i < n; i++) {
        int v = adj[cur][i];
        if(v != prev) {
            otherEnd[indexx[cur][i]] = v;
            dfs(v, cur, _depth + 1);
            subTreeSize[cur] += subTreeSize[v];
        }
    }
}

int main(void) {
    int tcase;
    scanf("%d", &tcase);
    while(tcase--) {
        ptr = 0;
        int n;
        scanf("%d", &n);
        // Cleaning step, new test case
        for(int i = 0; i < n; i++) {
            adj[i].clear();
            costs[i].clear();
            indexx[i].clear();
            chainHead[i] = -1;
            for(int j = 0; i < LogN; i++) table[i][j] = -1;
        }
        for(int i = 0; i < n - 1; i++) {
            int u, v, cost;
            scanf("%d %d %d", &u, &v, &cost);
            u--, v--;
            adj[u].push_back(v);
            costs[u].push_back(cost);
            indexx[u].push_back(i);
            adj[v].push_back(u);
            costs[v].push_back(cost);
            indexx[v].push_back(i);
        }
        
        chainNo = 0;
        dfs(); // We set up subTreeSize, depth and parent for each node
        HLD(); // We decomposed the tree and created baseArray
        
        buildSegTree(); // We use baseArray and construct the needed segment tree
        
        lcaInit(n);
        
        while(true) {
            char s[100];
            scanf("%s", s);
            if(s[0] == 'D') break;
            int a, b;
            scanf("%d %d", &a, &b);
            if(s[0] == 'Q') {
                query(a - 1, b - 1);
            } else {
                change(a - 1, b);
            }
        }
    }
    return 0;
}