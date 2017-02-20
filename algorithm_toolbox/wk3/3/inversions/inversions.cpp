#include <iostream>
#include <vector>

using std::vector;
using namespace std;
long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
    long long number_of_inversions = 0;
    if (right == left) return number_of_inversions;
    size_t ave = left + (right - left) / 2;
    number_of_inversions += get_number_of_inversions(a, b, left, ave);
    number_of_inversions += get_number_of_inversions(a, b, ave+1, right);
    //write your code here
    // merge
    size_t i = left, j = ave+1;
    size_t bi = left;
    while(i <= ave and j <=right){
        if(a[i] <= a[j]){
            b[bi++] = a[i++];
        }
        else{
            b[bi++] = a[j++];
            number_of_inversions += ave - i + 1;
        }
    }
    while(i <= ave)
        b[bi++] = a[i++];
    while(j <= right)
        b[bi++] = a[j++];
    for(i = left, bi = left; i <= right; ++i)
        a[i] = b[i];
//    cout << left << right << " ";
//    for (int aa : a)
//        cout << aa << " ";
//    cout << endl;
    return number_of_inversions;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    vector<int> b(a.size());
    std::cout << get_number_of_inversions(a, b, 0, a.size()-1) << '\n';
}
