#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void explore(vector<vector<int> > &adj, vector<int> &used, int x) {
    used[x] = 1;

    for(auto it = adj[x].begin(); it != adj[x].end(); ++it){
      if(!used[(*it)])
        explore(adj, used, *it);
    }

}

void dfs(vector<vector<int> > &adj, vector<int> &used, vector<int> &order, int x) {
    used[x] = 1;

    for(auto it = adj[x].begin(); it != adj[x].end(); ++it){
      if(!used[(*it)])
        dfs(adj, used, order, *it);
    }

    order.push_back(x);
}     

vector<int> toposort(vector<vector<int> > adj) {
  vector<int> used(adj.size(), 0);
  vector<int> order;
  
  for(int i = 0; i < adj.size(); ++i){
    if(!used[i])
      dfs(adj, used, order, i);
  }
  std::reverse(order.begin(), order.end());
  return order;
}

int number_of_strongly_connected_components(vector<vector<int> > adj) {
  int result = 0;
  
  vector<vector<int> > adj_rev(adj.size(), vector<int>());

  for(int i = 0; i < adj.size(); ++i){
    for(int j = 0; j < adj[i].size(); ++j){
      adj_rev[adj[i][j]].push_back(i);
    }
  }

  vector<int> order = toposort(adj_rev);

  vector<int> used(adj.size(), 0);

  for(int i = 0; i < order.size(); ++i){
    if(!used[order[i]]){
      explore(adj, used, order[i]);
      ++result;
    }
  }
  //   std::cout << order[i]+1 << " ";
  // std::cout << std::endl;




  // for(int i = 0; i < adj.size(); ++i){
  //   std::cout << i+1 << " : ";
  //   for(int j = 0; j < adj[i].size(); ++j){
  //     std::cout << adj[i][j]+1 << " ";
  //   }
  //   std::cout << std::endl;
  // }

  // for(int i = 0; i < adj_rev.size(); ++i){
  //   std::cout << i+1 << " : ";
  //   for(int j = 0; j < adj_rev[i].size(); ++j){
  //     std::cout << adj_rev[i][j]+1 << " ";
  //   }
  //   std::cout << std::endl;
  // }

  return result;
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
