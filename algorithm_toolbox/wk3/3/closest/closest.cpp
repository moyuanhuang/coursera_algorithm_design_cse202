#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <float.h>
#include <stdlib.h>

using namespace std;

bool cmpx(pair<int, int> p1, pair<int, int> p2){
  if(p1.first != p2.first)
    return p1.first > p2.first;
  else
    return p1.second > p2.second;
}

bool cmpy(pair<int, int> p1, pair<int, int> p2){
  return p1.second > p2.second;
}

double dis(pair<int, int> p1, pair<int, int> p2){
  return sqrt(pow(p1.first - p2.first,2) + pow(p1.second - p2.second,2));
}

double bruteForce(vector<pair<int, int> > pts, int l ,int r){
  double min = DBL_MAX;
  for (int i = l; i <= r; ++i)
    for (int j = i+1; j <= r; ++j)
      if (dis(pts[i], pts[j]) < min)
        min = dis(pts[i], pts[j]);
  return min;
}

double combine(vector< pair<int, int> > pts, float d)
{
    float min = d;  // Initialize the minimum distance as d
    sort(pts.begin(), pts.end(), cmpy);
    for (int i = 0; i < pts.size(); ++i)
        for (int j = i+1; j < pts.size() and (pts[j].second - pts[i].second) < min; ++j)
            if (dis(pts[i],pts[j]) < min)
                min = dis(pts[i], pts[j]);
    return min;
}

double helper(vector<pair<int, int> > &pts, int l, int r){
  if (l-r == 1)
    return dis(pts[l], pts[r]);
  int mid = l + (l-r)/2;
  pair<int, int> mid_pt = pts[mid];
  double dis1 = helper(pts, l, mid-1);
  double dis2 = helper(pts, mid+1, r);
  double d = min(dis1, dis2);

  vector<pair<int, int> > combined;
  for(int i =0; i <= pts.size(); i++)
    if(abs(pts[i].first - mid_pt.first) < d)
      combined.push_back(pts[i]);
  d = min(d, combine(combined, d));
  return d;
}

double minimal_distance(vector<pair<int, int> > &pts) {
  //write your code here
  sort(pts.begin(), pts.end(), cmpx);
  double ans = helper(pts, 0, pts.size()-1);
  return ans;
}


int main() {
  size_t n;
  std::cin >> n;
  vector<pair<int, int> > pts(n);
  for (size_t i = 0; i < n; i++) {
    int x, y;
    std::cin >> x>> y;
    pts[i] = make_pair(x,y);
  }
  // for(auto p :pts)
  //   cout << p.first << " " << p.second << endl;
  std::cout << std::fixed;
  std::cout << std::setprecision(9) << minimal_distance(pts) << "\n";
}
