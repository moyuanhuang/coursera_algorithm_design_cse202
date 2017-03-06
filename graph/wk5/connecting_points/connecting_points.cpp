#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;
struct pt{
	int x;
	int y;
	pt(int xx, int yy): x(xx), y(yy) {}
	pt(): x(0), y(0) {}
};

vector<pair<double, pair<int, int> > > generate_edges(vector<pt> pts){
  vector<pair<double, pair<int, int> > > ret;
  for(size_t i = 0; i < pts.size(); ++i){
    pt p1 = pts[i];
    for(size_t j = i + 1; j < pts.size(); ++j){
      pt p2 = pts[j];
      double weight = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
      pair<double, pair<int, int> > edge = make_pair(weight, make_pair(i, j));
      ret.push_back(edge);
    }
  }
  return ret;
}

class DisjointSet{
private:
	vector<int> parent_;
	vector<int> rank_;
	int n_;

public:
	DisjointSet(int n){
		n_ = n;
		parent_.resize(n);
		rank_.resize(n);
		for(size_t i = 0; i < n_; ++i){
			parent_[i] = i;
			rank_[i] = 0;
		}
	}

	int find(int idx){
		if(parent_[idx] != idx)
			parent_[idx] = find(parent_[idx]);
		return parent_[idx];
	}

	void join(int s1, int s2){
		s1 = find(s1);
		s2 = find(s2);
		if(rank_[s1] > rank_[s2])
			parent_[s2] = s1;
		else
			parent_[s1] = s2;
		if(rank_[s1] == rank_[s2])
			++rank_[s2];
	}
};


double minimum_distance(vector<pt> pts) {
  double result = 0.;
  //write your code here
  vector<pair<double, pair<int, int> > > edges = generate_edges(pts);
  sort(edges.begin(), edges.end());
  DisjointSet ds(pts.size());
  for(auto it = edges.begin(); it != edges.end(); ++it){
  	double weight = it->first;
  	int s1 = it->second.first;
  	int s2 = it->second.second;
  	
  	s1 = ds.find(s1);
  	s2 = ds.find(s2);
  	if(s1 != s2){
  		result += weight;
  		ds.join(s1, s2);
  	}
  }
  return result;
} 

int main() {
  size_t n;
  std::cin >> n;
  vector<pt> pts(n);
  for (size_t i = 0; i < n; i++) {
  	int x, y;
    std::cin >> x >> y;
    pts[i] = pt(x, y);
  }
  std::cout << std::setprecision(10) << minimum_distance(pts) << std::endl;
}
