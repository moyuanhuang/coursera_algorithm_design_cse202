#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int optimal_weight(int W, const vector<int> &w) {
  //write your code here
  if(w.empty()) return 0;
  vector<vector<int> > dp(W+1, vector<int>(w.size()+1, 0));
  for(int i = 1; i <= W; ++i){
    for(int j = 1; j <= w.size(); ++j){
      if(w[j-1] <= i){
        int residue = i - w[j-1];
        dp[i][j] = max(dp[residue][j-1] + w[j-1], dp[i][j-1]);
      }
      else
        dp[i][j] = dp[i][j-1];
    }
  }
  return dp[W][w.size()];
}

int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  sort(w.begin(), w.end());
  std::cout << optimal_weight(W, w) << '\n';
}
