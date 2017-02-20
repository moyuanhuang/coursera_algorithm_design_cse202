#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int partition2(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  return j;
}

pair<int, int> partition3(vector<int> &a, int l, int r) {
  // for(int aa : a)
  //   cout << aa << " ";
  // cout << "partition3" << endl;
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] < x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);

  int mid1 = j;
  for(int i = j + 1; i <= r; i++){
    if(a[i] == x){
      j++;
      swap(a[j], a[i]);
    }
  }
  return make_pair(mid1, j);
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  pair<int, int> p = partition3(a, l, r);
  // cout << endl << p.first << " " << p.second << endl;
  randomized_quick_sort(a, l, p.first - 1);
  randomized_quick_sort(a, p.second + 1, r);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  randomized_quick_sort(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }
}
