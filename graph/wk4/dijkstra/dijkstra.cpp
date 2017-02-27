#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>

using namespace std;

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int source, int target) {
	//write your code her
	unordered_map< int, long long > dist;
	vector< long long > prev( adj.size(), -1);
	for(int i = 0; i < adj.size(); ++i)
		dist[i] = INT_MAX;

	dist[source] = 0;

	auto cmp = [&dist]( int left, int right ){
    return dist[ left ] > dist[ right ];
  };
  priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);

	for(int i = 0; i < adj.size(); ++i)
		pq.push(i);

	while (!pq.empty()){
		int u = pq.top();
		pq.pop();

		vector<int> edges = adj[u];
		for(int v : edges) {
			int w = cost[u][v];
			if(dist[v] == INT_MAX){
				dist[v] = dist[ u ] + w;
				prev[v] = u;
				pq.push(v);
			}
			else{
				if (dist[ v ] > ( dist[ u ] + w )){
					dist[ v ] = dist[ u ] + w;
					prev[ v ] = u;
					pq.push( v );
				}
			}
		}
	}

	int tmp = target;
	int sum = 0;
	while(tmp != source){
		if (tmp == -1 || prev[tmp] == -1) return -1;
		int w = cost[prev[tmp]][tmp];
		if (w == -1) return -1;
		sum += w;
		tmp = prev[tmp];
	}
	return sum;
}

int main() {
	int n, m;
	std::cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	vector<vector<int> > cost(n, vector<int>(n, -1));
	for (int i = 0; i < m; i++) {
		int x, y, w;
		std::cin >> x >> y >> w;
		adj[x - 1].push_back(y - 1);
		// cost[x - 1].push_back(w);
    cost[x - 1][y - 1] = w;
	}
	int s, t;
	std::cin >> s >> t;
	s--, t--;
	std::cout << distance(adj, cost, s, t);
}
