#include <iostream>
#include <vector>

using std::vector;

vector<int> optimal_summands(long long n) {
  vector<int> summands;
  //write your code here
  for(long long i = 1; i <= n; i++){
    long long tmp = n - i;
    if(tmp > i or tmp == 0)
    {
      summands.push_back(i);
      n = tmp;
    }
  }
  return summands;
}

int main() {
  long long n;
  std::cin >> n;
  vector<int> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
}
