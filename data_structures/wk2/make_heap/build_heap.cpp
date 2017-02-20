#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class HeapBuilder {
private:
	vector<int> data_;
	vector< pair<int, int> > swaps_;

	void WriteResponse() const {
		cout << swaps_.size() << "\n";
		for (int i = 0; i < swaps_.size(); ++i) {
			cout << swaps_[i].first << " " << swaps_[i].second << "\n";
		}
	}

	void ReadData() {
		int n;
		cin >> n;
		data_.resize(n);
		for (int i = 0; i < n; ++i)
			cin >> data_[i];
	}

	void GenerateSwaps() {
		swaps_.clear();
		// The following naive implementation just sorts
		// the given sequence using selection sort algorithm
		// and saves the resulting sequence of swaps.
		// This turns the given array into a heap,
		// but in the worst case gives a quadratic number of swaps.
		//
		// TODO: replace by a more efficient implementation
		int count = data_.size() / 2;
		while (count >=  0) {
			shift_down(data_, count, swaps_);
			count--;
		}
	}

	void shift_down(vector<int> &data, int idx, vector<pair<int, int> > &ans) {
		int min_idx = idx;
		int first = idx;
		while(true){
			int left = idx * 2 + 1, right = idx*2 + 2;
			if(left < data.size() and data[left] < data[min_idx])
				min_idx = left;
			if(right < data.size() and data[right] < data[min_idx])
				min_idx = right;
			if(min_idx == first)	return;
			if(idx == min_idx){
				// ans.push_back(make_pair(first, min_idx));
				return;
			}
			else{
				swap(data[idx], data[min_idx]);
				ans.push_back(make_pair(idx, min_idx));
				idx = min_idx;
			}
		}
	}

public:
	void Solve() {
		ReadData();
		GenerateSwaps();
		WriteResponse();
		// for(int i = 0; i < data_.size(); i++)
		// 	cout << data_[i] << " ";
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	HeapBuilder heap_builder;
	heap_builder.Solve();
	return 0;
}
