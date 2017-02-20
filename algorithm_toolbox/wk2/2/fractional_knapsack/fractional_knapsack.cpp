#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(pair<long long, long long> p1, pair<long long, long long> p2){
  double vpw1 = (double)p1.first/(double)p1.second;
  double vpw2 = (double)p2.first/(double)p2.second;
  return  vpw1 > vpw2;
}
double get_optimal_value(long long capacity, vector<long long> weights, vector<long long> values) {
  double value = 0.0;

  // write your code here
  vector<pair<long long, long long> > vpw(weights.size());
  for(int i = 0; i < vpw.size(); i++){
    vpw[i] = make_pair(values[i],weights[i]);
  }
  sort(vpw.begin(), vpw.end(), cmp);
  for(pair<long long, long long> p: vpw){
    if(capacity >= p.second)
    {
      value += p.first;
      capacity -= p.second;
    }
    else{
      double unit = double(p.first)/double(p.second);
      value += unit * capacity;
      capacity = 0;
    }
    if(capacity == 0)  break;
  }
  return value;
}

int main() {
  int n;
  long long capacity;
  std::cin >> n >> capacity;
  vector<long long> values(n);
  vector<long long> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
