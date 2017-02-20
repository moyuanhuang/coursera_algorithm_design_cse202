#include <iostream>

using namespace std;
int gcd_naive(int a, int b) {
  while(a != 0 and b != 0)
  {
    int ma = max(a,b);
    int mi = min(a,b);
    a = mi;
    b = ma % mi;
  }
  return a == 0? b: a;
}

long long lcm_naive(int a, int b) {
  long long gcd = gcd_naive(a,b);
  return a / gcd * b;
}

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << lcm_naive(a, b) << std::endl;
  return 0;
}
