#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// void print(vector<vector<int> > adj){
//     for(int i = 0; i < adj.size(); i++){
//     cout << i+1 << " points to : ";
//     for(auto j: adj[i])
//       cout << j+1 << " ";
//     cout << endl;
//   }
//   return;
// }

vector<vector<int> > reverse_graph(vector<vector<int> > g){
  vector<vector<int> > ret(g.size(), vector<int>());
  for(int i = 0; i < g.size(); ++i)
    for(int j = 0; j < g[i].size(); ++j){
      // cout << g[i][j]+1 << "points to : " << i+1 <<endl;
      ret[g[i][j]].push_back(i); 
    }
  return ret;
}

void helper(vector<vector<int> > g, int vertex, stack<int>& s, vector<bool>& visited){
  visited[vertex] = true;
  for(int i : g[vertex])
    if(!visited[i])
      helper(g, i, s, visited);
  s.push(vertex);
}

int number_of_strongly_connected_components(vector<vector<int> > g) {
  vector<vector<int> > reverse_g = reverse_graph(g);
  stack<int> reverse_post_order;
  vector<bool> visited(g.size(), false);
  //write your code here
  // print(g);
  // cout << "========" << endl;
  // print(reverse_g);
  int count = -1;
  for(int i = 0; i < reverse_g.size(); ++i)
    if(!visited[i])
      helper(reverse_g, i, reverse_post_order, visited);
  count = 0;
  for(int i = 0; i < visited.size(); i++)
    visited[i] = false;
  // while(!reverse_post_order.empty()){
  //   cout << reverse_post_order.top() + 1<< " ";
  //   reverse_post_order.pop();
  // }
  while(!reverse_post_order.empty()){
    int vertex = reverse_post_order.top();
    // cout << vertex << " " << endl;
    reverse_post_order.pop();
    if(!visited[vertex]){
      helper(g, vertex, reverse_post_order, visited);
      ++count;
    }
  }
  return count;
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
  std::cout << number_of_strongly_connected_components(adj);
}
