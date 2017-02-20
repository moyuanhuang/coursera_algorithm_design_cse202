#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int get_majority_element(vector<int> &a, int left, int right) {
  int count = 0;
  int maj = -1;
  for(int i = 0; i < a.size(); i++){
    if(count == 0){
      count++;
      maj = a[i];
      continue;
    }
    if(maj == a[i]) count++;
    else count--;
  }
  count = 0;
  for(int i = 0; i < a.size(); i++)
    if(maj == a[i]) count++;
  return count > a.size()/2;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
    // cout << a[i] << endl;
  }
  std::cout << (get_majority_element(a, 0, a.size()) == 1) << '\n';
}
