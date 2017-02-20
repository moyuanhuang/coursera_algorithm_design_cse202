#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;
typedef unsigned long long ull;

ull hash_func(const string &str, int start, int end) {
    ull hash = 0;
    ull x = 263;
    ull p = 1000000007;
    for (int i = start; i < end; i++)
        hash += fmod(str[i] * x, p);
    return hash;
}

bool eql(const string &s, const string &t, int start, int end) {
    // cout << start << " " << end << endl << s << " " << t.substr(start, end - start) << " ";
    int i = 0;
    while (i < s.size()) {
        // cout << s[i] << "==" << t[i+start] << " ";
        if (s[i] != t[start + i]){
            // cout << " not equal" << endl;
            return false;
        }
        i++;
    }
    // cout << " equal" << endl;
    return true;
}

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    ull hs = hash_func(s, 0, s.size());
    // cout << hs << endl;
    for (int i = 0; i < t.size() - s.size() + 1; i++) {
        // string tmp = t.substr(i, s.size());
        ull ht = hash_func(t, i, i + s.size());
        if ( ht == hs and eql(s, t, i, i + s.size()))
            ans.push_back(i);
    }
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
