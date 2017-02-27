#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int distance(vector<vector<int> > &adj, int source, int target) {
  queue<int> q;
  vector<bool> visited(adj.size(), false);
  q.push(source);

  int result = 0;

  while(!q.empty()) {
    int size = q.size();
    result++;

    for(int i = 0; i < size; i++) {
      int node = q.front();
      q.pop();    
      visited[node] = true;  

      for(int i = 0; i < adj[node].size(); i++) {
        int neighbor = adj[node][i];
        if(!visited[neighbor]) {
          if(neighbor == target) {
            return result;
          }

          q.push(neighbor);
        }
      }
    }
  }

  return -1;
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}