#include <iostream>

int get_change(int m) {
	//write your code here
	int ans = 0;
	ans += m/10;
	m = m % 10;
	ans += m/5;
	m = m % 5;
	ans += m;
	return ans;
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
