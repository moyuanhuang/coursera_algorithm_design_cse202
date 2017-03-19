// #include <bits/stdc++.h>
#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

struct ConvertHampathToSat {
    double numVertices;
    int numEdges;
    vector<vector<int> > edges;
    ConvertHampathToSat(int n) :
        numVertices(n),
        edges(n)
    {  }

    vector<vector<int> > generate_idx(){
       vector<vector<int> > ret(numVertices, vector<int>(numVertices, 0));
        for(int i = 0; i < numVertices; ++i)
            for(int j = 0; j < numVertices; ++j)
                ret[i][j] = i * numVertices + j + 1;
        return ret;
    }

    void printEquisatisfiableSatFormula() {
        vector<vector<int> > idx = generate_idx();
        int clauses = numVertices * numVertices * numVertices;
        cout << clauses << " " << numVertices * numVertices << endl;
        // every node must be included
        // n
        int cnt = 0;
        for(int node = 0; node < numVertices; ++node){
            for(int i = 0; i < numVertices; ++i)
                cout << idx[i][node] << " ";
            cout << 0 << endl;
            ++cnt;
        }

        // No node appears twice
        // n * (n-1)/2 * n
        for(int node = 0; node < numVertices; ++node){
            for(int i = 0; i < numVertices; ++i)
                for(int j = i + 1; j < numVertices; ++j){
                    cout << -idx[i][node] << " " << -idx[j][node] << " 0" << endl;
                    ++cnt;
                }
        }

        // no nodes occupy the same position
        // n * (n-1)/2 * n
        for(int pos = 0; pos < numVertices; ++pos){
            for(int i = 0; i < numVertices; ++i)
                for(int j = i + 1; j < numVertices; ++j){
                    cout << -idx[pos][i] << " " << -idx[pos][j] << " 0" << endl;
                    ++cnt;
                }
        }

        // n * (n-1)
        for(int from = 0; from < numVertices; ++from){
            for(int pos = 0; pos < numVertices-1; ++pos){
                cout << -idx[pos][from] << " ";
                for(int to : edges[from]){
                    cout << idx[pos+1][to] << " ";
                }
                cout << 0 << endl;
                ++cnt;
            }
        }

        // for(int from = 0; from < numVertices; ++from){
        //     cout << from << " adjacent to ";
        //     for(int to : edges[from])
        //         cout << to << " ";
        //     cout << endl;
        // }
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertHampathToSat converter(n);
    vector<vector<bool> > has_edge(n, vector<bool>(n,false));
    int numEdges = 0;
    for (int i = 0; i < m; ++i) {
        int from, to;
        cin >> from >> to;
        if(has_edge[from-1][to-1] or has_edge[to-1][from-1])
            continue;
        has_edge[from-1][to-1] = true;
        has_edge[to-1][from-1] = true;
        converter.edges[from-1].push_back(to-1);
        converter.edges[to-1].push_back(from-1);
        ++numEdges;
    }
    converter.numEdges = numEdges;

    converter.printEquisatisfiableSatFormula();

    return 0;
}
