#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> compute_indegree(vector<vector<int> > &adj){
  vector<int> indegree(adj.size(), 0);
  for(int i = 0; i < adj.size(); i++)
    for(int j : adj[i])
      indegree[j]++;
  return indegree;
}

int acyclic(vector<vector<int> > &adj) {
  //write your code here
  vector<int> indegree = compute_indegree(adj);
  // for(int i = 0; i < indegree.size(); ++i)
  //   cout << i << " " << indegree[i] <<endl;
  queue<int> q;
  for(int i = 0; i < indegree.size(); ++i)
    if(indegree[i] == 0)
      q.push(i);
  while(!q.empty()){
    int vertex = q.front();
    q.pop();
    for(int i : adj[vertex]){
      --indegree[i];
      if(indegree[i] == 0)
        q.push(i);
    }
  }
  for(int i: indegree)
    if(i != 0)  return 1;
  return 0;
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
  // for(int i = 0; i < adj.size(); i++){
  //   cout << i << " points to : ";
  //   for(auto j : adj[i])
  //     cout << j << " ";
  //   cout << endl;
  // }
  std::cout << acyclic(adj);
}
