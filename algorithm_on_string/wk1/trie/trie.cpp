#include <string>
#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::string;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
  trie t;
  edges root;
  t.push_back(root);
  for(const string& p : patterns){
  	size_t cur_node = 0;
  	for(size_t i = 0; i < p.length(); ++i){
  		if(t[cur_node].count(p[i]) != 0)
  			cur_node = t[cur_node][p[i]];
  		else{
  			edges tmp;
  			t.push_back(tmp);
  			t[cur_node][p[i]] = t.size()-1;
  			cur_node = t[cur_node][p[i]];
  		}
  	}
  }
  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}