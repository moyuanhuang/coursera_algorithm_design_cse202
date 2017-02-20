#include <iostream>
#include <vector>

using namespace std;
long long get_period(long long p, vector<long long> &remainder){
    long long i = 2;
    long long prev = 0, cur = 1;
    while(true)
    {
        long long next =(cur + prev) % p;
        prev = cur;
        cur = next;
        ++i;
        remainder.push_back(cur);
        if(cur == 1 and prev == 0)  break;
    }
    remainder.erase(remainder.end()-2, remainder.end()-1);
    return i - 2;
}

long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;
    vector<long long> remainder;
    remainder.push_back(0);
    remainder.push_back(1);
    long long period = get_period(m, remainder);
    return remainder[n % period];
}

int main() {
    long long n, m;
    std::cin >> n >> m;
    std::cout << get_fibonacci_huge_naive(n, m) << '\n';
}
