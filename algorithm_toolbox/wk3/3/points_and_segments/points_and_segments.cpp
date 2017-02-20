#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool cmp(pair<int,char> a, pair<int, char> b){
  if(a.first != b.first) return a.first > b.first;
  return a.second > b.second;
}
unordered_map<int, int> fast_count_segments(vector< pair<int, char> > series, int num_pts) {
  unordered_map<int, int> mmap;
  sort(series.begin(), series.end());
  int tmp = 0;
  for(auto s:series)
    if(s.second == '0') tmp++;
    else if(s.second == '1') mmap[s.first] = tmp;
    else if(s.second == '2') tmp--;
  return mmap;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < starts.size(); j++) {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return cnt;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<pair<int, char> > series;
  for (size_t i = 0; i < n; i++) {
    int a, b;
    std::cin >> a >> b;
    series.push_back(make_pair(a,'0'));
    series.push_back(make_pair(b,'2'));
  }
  vector<int> points(m);
  for (size_t i = 0; i < m; i++) {
    std::cin >> points[i];
    series.push_back(make_pair(points[i],'1'));
  }
  //use fast_count_segments
  unordered_map<int, int> mmap = fast_count_segments(series, m);
  for (size_t i = 0; i < points.size(); i++) {
    std::cout << mmap[points[i]] << ' ';
  }
}
