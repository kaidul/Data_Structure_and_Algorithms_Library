#include <vector>
#include <array>
#include <queue>

using namespace std;

#define MAX 100000

vector<int> adj[MAX];
array<int, MAX> color;
array<bool, MAX> visited;

bool isGraphBipartite(int src) {
  color.fill(-1);
  visited.fill(false);
  queue<int> Q;
  Q.push(src);
  color[src] = 1;
  visited[src] = true;
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    for (int i = 0; i < (int)adj[u].size(); i++) {
      int v = adj[u][i];
      if (!visited[v]) {
        visited[v] = true;
        color[v] = 1 - color[u];
        Q.push(v);
      } else if (visited[v] and color[v] == color[u]) {
        return false;
      }
    }
  }
  return true;
}