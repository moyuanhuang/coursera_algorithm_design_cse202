#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void helper(vector<vector<int> > &adj, int x, int y, unordered_map<int, bool> umap, int &ans){
  umap[x] = true;
  for(int i: adj[x]){
    if(umap.count(i) != 0)  continue;
    if(i == y){
      ans = 1;
      return;
    }
    helper(adj, i, y, umap, ans);
    if(ans == 1) return;
  }
  return;
}

int reach(vector<vector<int> > &adj, int x, int y) {
  //write your code here
  unordered_map<int, bool> umap;
  int ans = 0;
  helper(adj, x, y, umap, ans);
  return ans;
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
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}
