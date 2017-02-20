#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;

struct cmp{
  bool operator()(pair<int, long long> a, pair<int, long long> b){
    return a.second > b.second
  }

};

class JobQueue {
 private:
  int num_workers_;
  queue<long long> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    for(int i = 0; i < m; ++i){
      long long tmp = 0;
      cin >> tmp;
      jobs_.push(tmp);
    }
  }

  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    priority_queue<pair<int, long long>, vector<pair<long long>, compare> workers;
    int busy_workers = 0;
    while(!jobs_.empty()){
      long long process_time = jobs_.front();
      jobs_.pop();
      if(busy_workers < num_workers_){
        workers.push(make_pair(busy_workers, process_time));
        busy_workers++;
        start_times_.push_back(0);
        assigned_workers_.push_back()
      }

    }

    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
