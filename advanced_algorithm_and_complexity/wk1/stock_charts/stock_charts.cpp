#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <queue>
#include <climits>
#include <fstream>

using namespace std;

struct Edge {
    int from, to, capacity, flow;
};
/* This class implements a bit unusual scheme for storing edges of the graph,
 * in order to retrieve the backward edge for a given edge quickly. */
class FlowGraph {
private:
    /* List of all - forward and backward - edges */
    vector<Edge> edges;

    /* These adjacency lists store only indices of edges in the edges list */
    vector<vector<size_t> > graph;

public:
    explicit FlowGraph(size_t n): graph(n) {}

    void add_edge(int from, int to, int capacity) {
        /* Note that we first append a forward edge and then a backward edge,
         * so all forward edges are stored at even indices (starting from 0),
         * whereas backward edges are stored at odd indices in the list edges */
        Edge forward_edge = {from, to, capacity, 0};
        Edge backward_edge = {to, from, 0, 0};
        graph[from].push_back(edges.size());
        edges.push_back(forward_edge);
        graph[to].push_back(edges.size());
        edges.push_back(backward_edge);
    }

    size_t size() const {
        return graph.size();
    }

    const vector<size_t>& get_ids(int from) const {
        return graph[from];
    }

    const Edge& get_edge(size_t id) const {
        return edges[id];
    }

    void add_flow(size_t id, int flow) {
        /* To get a backward edge for a true forward edge (i.e id is even), we should get id + 1
         * due to the described above scheme. On the other hand, when we have to get a "backward"
         * edge for a backward edge (i.e. get a forward edge for backward - id is odd), id - 1
         * should be taken.
         *
         * It turns out that id ^ 1 works for both cases. Think this through! */
        edges[id].flow += flow;
        edges[id].capacity -= flow;
        // edges[id ^ 1].flow -= flow;
        edges[id ^ 1].capacity += flow;
    }

    void print(){
        for(size_t from = 1; from < graph.size()-1; ++from){
            for(size_t to = 1; to < graph[from].size()-1; ++to)
                cout << "edge No." << graph[from][to] << " : from " << edges[graph[from][to]].from << " --> " << 
            edges[graph[from][to]].to << 
            " capacity : " << edges[graph[from][to]].flow << "/" << edges[graph[from][to]].capacity << endl;
        }
    }

    void print(string file_name){
        ofstream fs;
        fs.open(file_name);
        for(size_t from = 1; from < graph.size()-1; ++from){
            for(size_t to = 1; to < graph[from].size()-1; ++to)
              if(edges[graph[from][to]].flow == 0)
                continue;
              else
                fs << "edge No." << graph[from][to] << " : from " << edges[graph[from][to]].from << " --> " << 
            edges[graph[from][to]].to << 
            " capacity : " << edges[graph[from][to]].flow << "/" << edges[graph[from][to]].capacity << endl;
        }
        fs.close();
    }
};

int find_min_flow(FlowGraph& graph, vector<int>& path){
    int ret = INT_MAX;
    for(int eid : path){
        // cout << eid << " " << graph.get_edge(eid).capacity << " --> ";
        ret = min(ret, graph.get_edge(eid).capacity);
    }
    // cout << endl;
    return ret;
}

int find_path(FlowGraph& graph, vector<int>& path, int from, int to){
    queue<vector<int> > q;
    vector<bool> visited(graph.size(), false);
    for(auto eid : graph.get_ids(from))
        if(graph.get_edge(eid).capacity != 0)
            q.push(vector<int>(1, eid));
    visited[from] = true;


    while(!q.empty()){
        vector<int> tmp = q.front();
        q.pop();
        Edge e = graph.get_edge(tmp.back());
        // cout << "visiting edge from " << e.from << " --> " << e.to << endl;
        if(e.to == to){
            // cout << "found. returning..." << endl;
            path = tmp;
            return find_min_flow(graph, path);
        }
        for(auto eid : graph.get_ids(e.to)){
            Edge e_child = graph.get_edge(eid);
            // cout << "one of the edge from " << e.to << " is: e_" << eid << "  " <<  e_child.from << " --> " << e_child.to << endl;
            if(e_child.capacity <= 0 or visited[e_child.to])
                continue;
            if(e_child.to == to){
                // cout << "found. returning..." << endl;
                tmp.push_back(eid);
                path = tmp;
                return find_min_flow(graph, path);
            }
            tmp.push_back(eid);
            q.push(tmp);
            tmp.pop_back();
            visited[e_child.from] = true;
        }
    }
    return -1;
}

int max_flow(FlowGraph& graph, int from, int to) {
    int flow = 0;
    /* your code goes here */
    while(true){
        vector<int> path;
        int f = find_path(graph, path, from, to); 
        // cout << f << endl;
        if(f == -1) break;
        for(int eid : path){
            graph.add_flow(eid, f);
        }
    }
    for(size_t id : graph.get_ids(from))
        flow += graph.get_edge(id).flow;
    return flow;
}

class StockCharts {
 public:
  void Solve() {
    vector<vector<int>> stock_data = ReadData();
    int result = MinCharts(stock_data);
    WriteResponse(result);
  }

 private:
  vector<vector<int>> ReadData() {
    int num_stocks, num_points;
    cin >> num_stocks >> num_points;
    vector<vector<int>> stock_data(num_stocks, vector<int>(num_points));
    for (int i = 0; i < num_stocks; ++i)
      for (int j = 0; j < num_points; ++j) {
        cin >> stock_data[i][j];
      }
    return stock_data;
  }

  void WriteResponse(int result) {
    cout << result << "\n";
  }

  int MinCharts(const vector<vector<int>>& stock_data) {
    int num_stocks = stock_data.size();
    // build graph
    FlowGraph graph(2 + 2 * num_stocks);
    for(int i = 0; i < num_stocks; ++i)
      graph.add_edge(0, i + 1, 1);
    for(int i = 0; i < num_stocks; ++i){
      for(int j = i + 1; j < num_stocks; ++j){
        if(compare(stock_data[i], stock_data[j]))
          // add edge from stock_i --> stock_j, since stock_i > stock_j
          graph.add_edge(1 + i, num_stocks + 1 + j, 1);
        else if(compare(stock_data[j], stock_data[i]))
          graph.add_edge(1 + j, num_stocks + 1 + i, 1);
      }
    }
    for(int i = 0; i < num_stocks; ++i)
      graph.add_edge(num_stocks + 1 + i, 2 * num_stocks + 1, 1);

    int maxflow = max_flow(graph, 0, 2 * num_stocks + 1);
    return num_stocks - maxflow;
  }

  bool compare(const vector<int>& stock1, const vector<int>& stock2) {
    for (int i = 0; i < stock1.size(); ++i)
      if (stock1[i] <= stock2[i])
        return false;
    return true;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  StockCharts stock_charts;
  stock_charts.Solve();
  return 0;
}
