#include <iostream>
#include <limits>
#include <unordered_map>
#include <unordered_set>
// #include <pair>
#include <vector>
#include <cstdint>

using namespace std;

struct Vertex{
  long long val;
  bool inf;
	Vertex() : inf( true ), val( 0 ) {}
	Vertex( long long val ) : inf( false ), val( val ) {}
};

inline Vertex operator+( const Vertex &v, long long add_on){
	if(v.inf)
		return Vertex();
	return Vertex(v.val + add_on);
}

inline bool operator>( const Vertex &n1, const Vertex &n2){
	if ( !n1.inf && !n2.inf )  return n1.val > n2.val;
	if ( n1.inf && !n2.inf ) return true;
	if ( !n1.inf && n2.inf ) return false;
	return false;
}

inline bool relax(int u, int v, unordered_map<int, Vertex > &dist, const vector<vector<long long> > &cost ){
	Vertex temp = dist[ u ] + cost[ u ][ v ];
	Vertex &VertexV = dist[ v ];
	if(VertexV > temp){
		VertexV = temp;
		return true;
	}
	return false;
}

void helper(vector<vector<int> > &adj, vector<bool> &visited, int v){
	visited[v] = true;
	vector<int> neighbor = adj[ v ];
	for(int w : neighbor )
		if (!visited[ w ])
			helper(adj, visited, w);
}

unordered_set<int> bfs(vector<vector<int> > &adj, unordered_set<int> &from){
	unordered_set<int> uset;
	for(int f : from ){
		vector<bool> visited(adj.size(), false);
		helper( adj, visited, f );
		for (int i = 0; i < visited.size(); ++i )
			if (visited[i])
				uset.insert(i);
	}
	return uset;
}

pair<unordered_set<int>, unordered_map<int, Vertex> >
find_path(vector<vector<int> > &adj, vector<vector<long long> > &cost, int s){
	unordered_map<int, Vertex> dist;
  unordered_set<int> cycles;
	for(int i = 0; i < adj.size(); ++i )
		dist[i] = Vertex();
	dist[s] = Vertex(0ll);
	int size = adj.size();
	for(int i = 0; i < size; ++i )
		for (int j = 0; j < adj.size(); ++j )
		{
			int u = j;
			vector<int> neighbor = adj[u];
			for (int v : neighbor )
				if (relax( u, v, dist, cost ) and i == (size - 1))
						cycles.insert( v );
		}
	return {bfs( adj, cycles ), dist};
}

void shortest_paths(vector<vector<int> > &adj, vector<vector<long long> > &cost, int s,
                     vector< long long > &distance, vector<bool> &reachable, vector<bool> &shortest ){
	unordered_set<int> cycles;
	unordered_map<int, Vertex > dist;
	tie( cycles, dist ) = find_path( adj, cost, s );
	for (int i = 0; i < adj.size(); ++i ){
		if (i == s){
			reachable[i] = true;
			distance[i] = 0ll;
			continue;
		}
		reachable[i] = !dist[ i ].inf;
		if(reachable[i]){
			if(cycles.find(i) == cycles.end())
				distance[ i ] = dist[ i ].val;
			else
				shortest[ i ] = false;
		}
	}
}

int main()
{
	int n, m, s;
	cin >> n >> m;

	vector< vector<int> > adj( n, vector<int>() );
	vector< vector< long long > > cost( n, vector< long long >( n, -1 ) );

	for (int i = 0; i < m; i++ )
	{
		int x, y;
		long long w;
		cin >> x >> y >> w;

		adj[ x - 1 ].push_back( y - 1 );
		cost[ x - 1 ][ y - 1 ] = w;
	}

	cin >> s;
	s--;

	vector< long long > distance( n, numeric_limits< long long >::max() );
	vector< bool > reachable( n, false );
	vector< bool > shortest( n, true );
	shortest_paths( adj, cost, s, distance, reachable, shortest );
	for ( long long i = 0; i < n; i++ )
	{
		if ( !reachable[ i ] )
		{
			cout << "*\n";
		}
		else if ( !shortest[ i ] )
		{
			cout << "-\n";
		}
		else
		{
			cout << distance[ i ] << "\n";
		}
	}

	return 0;
}