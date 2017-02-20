#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

class TreeOrders {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;

public:
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }


  vector <int> in_order() {
    vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
    stack<int> s;
    s.push(0);
    int cur = left[0];
    while(!s.empty() or cur != -1){
      while(cur != -1){
        s.push(cur);
        cur = left[cur];
      }
      cur = s.top();
      s.pop();
      result.push_back(key[cur]);
      cur = right[cur];
    }
    return result;
  }

  vector <int> pre_order() {
    vector<int> result;    
    // Finish the implementation
    // You may need to add a new recursive method to do that
    stack<int> s;
    s.push(0);
    while(!s.empty()){
      int size = s.size();
      for(int i = 0; i < size; ++i){
        int tmp = s.top();
        s.pop();
        result.push_back(key[tmp]);
        if(right[tmp] != -1)  s.push(right[tmp]);
        if(left[tmp] != -1) s.push(left[tmp]);
      }
    } 
    return result;
  }

  vector <int> post_order() {
    vector<int> result;
    // Finish the implementation
    // You may need to add a new recursive method to do that
    stack<int> s;
    s.push(0);
    while(!s.empty()){
      int tmp = s.top();
      if(left[tmp] == -1 and right[tmp] == -1){
        result.push_back(key[tmp]);
        s.pop();
      }
      else{
        if(right[tmp] != -1){
          s.push(right[tmp]);
          right[tmp] = -1;
        }
        if(left[tmp] != -1){
          s.push(left[tmp]);
          left[tmp] = -1;
        }
      }
    }
    return result;
  }
};

void print(vector <int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  print(t.in_order());
  print(t.pre_order());
  print(t.post_order());
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}

