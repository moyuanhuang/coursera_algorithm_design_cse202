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

FlowGraph build_graph(const vector<vector<bool> > &adj_matrix) {
    int num_left = adj_matrix.size();
    int num_right = adj_matrix[0].size();
    FlowGraph graph(2 + num_left + num_right);
    for(int i = 0; i < num_left; ++i){
      graph.add_edge(0, 1 + i, 1);
      for(int j = 0; j < num_right; ++j)
        // index of right: num_left + 1 + j 
        if(adj_matrix[i][j])  graph.add_edge(1 + i, num_left + 1 + j, 1);
    }
    for(int j = 0; j < num_right; ++j)
      // index of sink point: num_left + num_right + 1
      graph.add_edge(num_left + 1 + j, num_left + num_right + 1, 1);
    return graph;
}

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

class MaxMatching {
 public:
  void Solve() {
    vector<vector<bool>> adj_matrix = ReadData();
    vector<int> matching = FindMatching(adj_matrix);
    WriteResponse(matching);
  }

 private:
  vector<vector<bool>> ReadData() {
    int num_left, num_right;
    cin >> num_left >> num_right;
    vector<vector<bool>> adj_matrix(num_left, vector<bool>(num_right));
    for (int i = 0; i < num_left; ++i)
      for (int j = 0; j < num_right; ++j) {
        int bit;
        cin >> bit;
        adj_matrix[i][j] = (bit == 1);
      }
    return adj_matrix;
  }

  void WriteResponse(const vector<int>& matching) {
    for (int i = 0; i < matching.size(); ++i) {
      if (i > 0)
        cout << " ";
      if (matching[i] == -1)
        cout << "-1";
      else
        cout << (matching[i] + 1);
    }
    cout << "\n";
  }

  vector<int> FindMatching(const vector<vector<bool>>& adj_matrix) {
    // Replace this code with an algorithm that finds the maximum
    // matching correctly in all cases.
    int num_left = adj_matrix.size();
    int num_right = adj_matrix[0].size();
    vector<int> matching(num_left, -1);
    FlowGraph graph = build_graph(adj_matrix);
    // string file_name("before.txt");
    // graph.print(file_name);
    max_flow(graph, 0, num_left + num_right + 1);
    for(int i = 0; i < num_left; ++i){
      for(auto eid : graph.get_ids(1+i)){
        Edge e = graph.get_edge(eid);
        if(e.flow == 1){
          matching[e.from - 1] = e.to - num_left - 1;
         }
      }
    }
    // file_name = "after.txt";
    // graph.print(file_name);
    return matching;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  MaxMatching max_matching;
  max_matching.Solve();
  return 0;
}
