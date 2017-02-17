vector <int> adj[Max];
int visited[Max], dis[Max + 1];
queue <int> q;
 
void BFS(int src) {
    q.push(src);
    dis[src] = 0;
    visited[src] = true;
    printf("Level %d: %d\n", dis[src], src);
    while(!q.empty()) {
        int pop = q.front(), temp;
        for(int i = 0, n = (int)adj[pop].size(); i < n; i++) {
            temp = adj[pop][i];
            if(!visited[temp]) {
                dis[temp] = dis[pop] + 1;
                visited[temp] = 1;
                q.push(temp);
                printf("Level %d: %d\n", dis[temp], temp);
            }
        }
        q.pop();
    }
}