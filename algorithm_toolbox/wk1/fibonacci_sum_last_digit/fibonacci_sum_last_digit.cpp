#include <iostream>
#include <vector>

using namespace std;

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

int fibonacci_sum_advanced(long long n)
{
    vector<int> remainder;
    remainder.push_back(0);
    remainder.push_back(1);
    int period = get_period(10, remainder);
    int last_digit = 0;
    for(int i = 0; i <= n % 60; ++i){
        last_digit += remainder[i];
    }
    last_digit %= 10;
    return last_digit;
}

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;
    int prev = 0;
    int cur = 1;
    int sum = 1;
    for(long long i = 2; i <= n; i++)
    {
        int next = (prev + cur) % 10;
        sum = (sum + next) % 10;
        prev = cur;
        cur = next;
    }
    return sum;
}

int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_advanced(n);
}


