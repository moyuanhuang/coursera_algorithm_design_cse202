#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

vector<int> optimal_sequence(int n) {
  vector<int> dp(n+1, 0);
  dp[1] = 0;
  for(int i = 2; i <= n; i++){
    int a = dp[i-1] + 1;
    int b = INT_MAX, c = INT_MAX;
    if(i % 2 == 0)  b = dp[i/2] + 1;
    if(i % 3 == 0)  c = dp[i/3] + 1;
    dp[i] = min(min(a,b),c);
  }
  return dp;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> dp = optimal_sequence(n);
  int i = n;
  cout << dp[n] << endl;
  vector<int> sequence;
  while(i >= 1){
    sequence.push_back(i);
    if(i == 1)  break;
    int prev = dp[i]-1;
    if(dp[i-1] == prev) i = i - 1;
    else if(i % 2 == 0 and dp[i/2] == prev) i = i /2;
    else if(i % 3 == 0 and dp[i/3] == prev) i = i /3;
  }
  reverse(sequence.begin(), sequence.end());
  for(int s : sequence)
    cout << s << " ";
  return 0;
}
