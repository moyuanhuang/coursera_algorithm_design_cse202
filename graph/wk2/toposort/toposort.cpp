#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

// void dfs(vector<vector<int> > &adj, vector<int> &used, vector<int> &order, int x) {
//   //write your code here
// }     

vector<int> toposort(vector<vector<int> > adj) {
  // vector<int> used(adj.size(), 0);
  vector<int> indegree(adj.size(), 0);
  vector<int> order;
  for(auto v: adj)
    for(int i : v)
      indegree[i]++;
  queue<int> q;
  for(int i = 0; i < indegree.size(); ++i)
    if(indegree[i] == 0)  q.push(i);
  while(!q.empty()){
    int vertex = q.front();
    q.pop();
    for(int v2: adj[vertex]){
      indegree[v2]--;
      if(indegree[v2] == 0) q.push(v2);
    }
    order.push_back(vertex);
  }
  return order;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  vector<int> order = toposort(adj);
  for (size_t i = 0; i < order.size(); i++) {
    std::cout << order[i] + 1 << " ";
  }
}
