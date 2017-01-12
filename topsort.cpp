// works but visit same node twice in case like (1->2, 1->3, 3->2)
bool hasLoop(int node, vector<vector<int>>& adj, vector<bool>& marked) {
    if(marked[node]) {
        return true;
    }
    marked[node] = true;
    for(int i = 0; i < (int)adj[node].size(); ++i) {
        int neigh = adj[node][i];
        if(hasLoop(neigh, adj, marked)) {
            return true;
        }
    }
    marked[node] = false;
    return false;
}


// The Cormen way
enum {WHITE, GRAY, BLACK};

bool hasLoop2(int node, vector<vector<int>>& adj, vector<int>& color) {
    if(color[node] == BLACK) {
        return false;
    }
    if(color[node] == GRAY) {
        return true;
    }
    color[node] = GRAY;
    for(int i = 0; i < (int)adj[node].size(); ++i) {
        int neigh = adj[node][i];
        // if self loop allowed
        // if(neigh == node) continue;
        if(hasLoop2(neigh, adj, color)) {
            return true;
        }
    }
    color[node] = BLACK;
    
    return false;
}

void topsortUtil(int u, vector<vector<int>>& adj, vector<bool>& visited, vector<int>& result
                /*, vector<int>& parent, vector<int>& discover, vector<int>& finish, int& time */) {
    visited[u] = true;
//    discover[u] = ++time;
    for(int i = 0; i < (int)adj[u].size(); i++) {
        if(!visited[adj[u][i]]) {
//            parent[adj[u][i]] = u;
            topsortUtil(adj[u][i], adj, visited, result/*, parent, discover, finish, time */);
        }
    }
    result.push_back(u);
//    finish[u] = ++time;
}

void topsort(int n, vector<vector<int>>& adj, vector<int>& result) {
    vector<bool> visited(n + 1, false);
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            topsortUtil(i, adj, visited, result);
        }
    }
    // reverse(result.begin(), result.end());
}