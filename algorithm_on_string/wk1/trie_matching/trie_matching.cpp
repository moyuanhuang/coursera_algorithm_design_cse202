#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];

	Node ()
	{
		fill (next, next + Letters, NA);
	}

	bool isLeaf () const
	{
		return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
	}
};

typedef vector<Node> trie;

int letterToIndex (char letter)
{
	switch (letter)
	{
	case 'A': return 0; break;
	case 'C': return 1; break;
	case 'G': return 2; break;
	case 'T': return 3; break;
	default: cout << letter << endl; assert (false); return -1;
	}
}

trie build_trie(const vector<string> & patterns) {
  trie t;
  Node root;
  t.push_back(root);
  for(const string& p : patterns){
  	size_t cur_node = 0;
  	for(size_t i = 0; i < p.length(); ++i){
  		size_t next_i = letterToIndex(p[i]);
  		if(t[cur_node].next[next_i] != NA)
  			cur_node = t[cur_node].next[next_i];
  		else{
  			Node tmp;
  			t.push_back(tmp);
  			t[cur_node].next[next_i] = t.size()-1;
  			cur_node = t[cur_node].next[next_i];
  		}
  	}
  }
  return t;
}

vector <int> solve (const string& text, int n, const vector <string>& patterns)
{
	vector <int> result;
	trie t = build_trie(patterns);
	// for (size_t i = 0; i < t.size(); ++i) {
	// 	for(size_t j = 0; j < Letters; ++j)
 //    		if( t[i].next[j] != NA)
 //      			std::cout << i << "->" << j << ":" << t[i].next[j] << "\n";
 //      	if(t[i].isLeaf())
 //      			std::cout << i << "leafNode\n";
 //    }
	for(size_t i = 0; i < text.length(); ++i){
		size_t cur_node = 0;
		size_t cur_symb = i;
		while(true){
			if(t[cur_node].isLeaf()){
				result.push_back(i);
				break;
			}
			else if(cur_symb < text.length() and t[cur_node].next[letterToIndex(text[cur_symb])] != NA){
				cur_node = t[cur_node].next[letterToIndex(text[cur_symb])];
				cur_symb++;
				// cout << cur_symb << " " << text[cur_symb] << endl;
			}
			else
				break;
		}
	}
	return result;
}

int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
