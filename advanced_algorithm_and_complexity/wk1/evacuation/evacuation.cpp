#include <iostream>
#include <vector>
#include <queue>
#include <climits>

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
        edges[id ^ 1].flow -= flow;
        edges[id ^ 1].capacity += flow;
    }

    void print(){
        for(size_t from = 0; from < graph.size(); ++from){
            for(size_t to = 0; to < graph[from].size(); ++to)
                cout << "edge No." << graph[from][to] << " : from " << edges[graph[from][to]].from << " --> " << 
            edges[graph[from][to]].to << " capacity : " << edges[graph[from][to]].capacity << endl;
        }
    }
};

FlowGraph read_data() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    FlowGraph graph(vertex_count);
    for (int i = 0; i < edge_count; ++i) {
        int u, v, capacity;
        std::cin >> u >> v >> capacity;
        graph.add_edge(u - 1, v - 1, capacity);
    }
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
            if(e_child.capacity == 0 or visited[e_child.to])
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

int main() {
    std::ios_base::sync_with_stdio(false);
    FlowGraph graph = read_data();
    // graph.print();
    std::cout << max_flow(graph, 0, graph.size() - 1) << "\n";
    return 0;
}
