#include <iostream>
#include <vector>
using std::vector;

int get_period(int p, vector<int> &remainder){
    int i = 2;
    int prev = 0, cur = 1;
    while(true)
    {
        int next =(cur + prev) % p;
        prev = cur;
        cur = next;
        ++i;
        remainder.push_back(cur);
        if(cur == 1 and prev == 0)  break;
    }
    remainder.erase(remainder.end()-2, remainder.end()-1);
    return i - 2;
}


long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    if (to <= 1)
        return to;
    vector<int> remainder;
    remainder.push_back(0);
    remainder.push_back(1);
    int period = get_period(10, remainder);
    int last_digit = 0;
    for(int i = from % 60; i <= to % 60; ++i){
        last_digit += remainder[i];
    }
    last_digit %= 10;
    return last_digit;
    
}

int main() {
    long long from, to;
    std::cin >> from >> to;
    std::cout << get_fibonacci_partial_sum_naive(from, to) << '\n';
}
