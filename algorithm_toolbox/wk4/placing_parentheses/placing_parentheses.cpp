#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <sstream>
#include <climits>

using namespace std;

long long eval(long long a, long long b, char op) {
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
    assert(0);
  }
}

pair<long long, long long> minAndMax(int i,int j, const vector<long long> &nums, const vector<char> &ops,
  vector<vector<long long> >& mi, vector<vector<long long > >& ma){
  long long ans_max = LLONG_MIN;
  long long ans_min = LLONG_MAX;
  for(int k = i; k < j; k++){
    long long a = eval(ma[i][k], ma[k+1][j], ops[k]);
    long long b = eval(ma[i][k], mi[k+1][j], ops[k]);
    long long c = eval(mi[i][k], ma[k+1][j], ops[k]);
    long long d = eval(mi[i][k], mi[k+1][j], ops[k]);
    ans_max = max(max(max(a,b), max(c,d)), ans_max);
    ans_min = min(min(min(a,b), min(c,d)), ans_min);
  }
  return make_pair(ans_min, ans_max);
}

long long get_maximum_value(const vector<long long> &nums, const vector<char> &ops) {
  //write your code here
  int n = nums.size();
  if(n == 0)  return 0;
  if(n == 1)  return nums[n-1];
  vector<vector<long long> > mi(n, vector<long long>(n, 0));
  vector<vector<long long> > ma(n, vector<long long>(n, 0));
  for(size_t i = 0; i < n; i++){
    mi[i][i] = nums[i];
    ma[i][i] = nums[i];
  }
  for(size_t s = 1; s <= n-1; s++)
  {
    for(size_t i = 0; i < n - s; i++)
    {
      int j = i + s;
      pair<long long, long long> min_and_max = minAndMax(i, j, nums, ops, mi, ma);
      mi[i][j] = min_and_max.first;
      ma[i][j] = min_and_max.second;
    }
  }
  return ma[0][n-1];
}

int main() {
  stringstream ss;
  string s;
  std::cin >> s;
  ss << s;
  long long a = 0;
  char op = 0;
  vector<long long> nums;
  vector<char> ops;
  while(!ss.eof()){
    ss >> a;
    // if(ss.eof())
    //   break;
    nums.push_back(a);
    ss >> op;
    ops.push_back(op);
  }
  std::cout << get_maximum_value(nums, ops) << '\n';
}
