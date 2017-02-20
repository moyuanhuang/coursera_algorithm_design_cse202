#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using namespace std;

struct Segment {
  int start, end;
};

bool cmp(Segment a, Segment b){
  return a.start < b.start;
}

vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;
  //write your code here
  sort(segments.begin(), segments.end(), cmp);
  // for(auto s : segments){
  //   cout << s.start << " " << s.end << endl;
  // }
  for (size_t i = 0; i < segments.size(); ++i) {
    points.push_back(segments[i].end);
    while(i + 1 < segments.size() and segments[i+1].start <= segments[i].end){
      if(segments[i+1].end < segments[i].end){
        ++i;
        // cout << i << endl;
        *(points.end()-1) = segments[i].end;
      }
      else
        segments.erase(segments.begin() + i + 1);
    }
  }
  return points;
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}
