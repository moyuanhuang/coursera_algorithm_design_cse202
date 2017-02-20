#include <iostream>
#include <vector>

using namespace std;

void helper(vector<vector<int> > &adj, int i, vector<bool> &visited){
  visited[i] = true;
  for(int pt : adj[i]){
    if(visited[pt]) continue;
    helper(adj, pt, visited);
  }
  return;
}

int number_of_components(vector<vector<int> > &adj) {
  int cnt = 0;
  //write your code here
  int num_v = adj.size();
  vector<bool> visited(num_v, false);
  for(int i = 0; i < num_v; ++i){
    if(visited[i])  continue;
    ++cnt;
    helper(adj, i, visited);
  }
  return cnt;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj);
}
