#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int bipartite(vector<vector<int> > &adj) {
  queue<int> q;
  vector<int> color(adj.size(), 0);
  color[0] = 1;
  q.push(0);
  while(!q.empty()) {
    int node = q.front();
    q.pop();
    for(int i = 0; i < adj[node].size(); i++) {
      int neighbor = adj[node][i];
      if (color[neighbor] == 0) {
        if (color[node] == 1) color[neighbor] = 2;
        else                  color[neighbor] = 1;
        q.push(neighbor);
      }
      else if (color[neighbor] == color[node])
        return 0;
    }
  }
  return 1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj);
}