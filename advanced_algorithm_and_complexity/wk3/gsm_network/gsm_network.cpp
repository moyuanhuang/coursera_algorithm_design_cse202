#include <ios>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct ConvertGSMNetworkProblemToSat {
    int numVertices;
    int numEdges;
    vector<pair<int, int> > edges;
    ConvertGSMNetworkProblemToSat(int n, int m) :
        numVertices(n),
        numEdges(m)

    {  }

    vector<vector<int> > generate_idx(){
        vector<vector<int> > ret(numVertices, vector<int>(3, 0));
        for(int i = 0; i < numVertices; ++i)
            for(int j = 0; j < 3; ++j)
                ret[i][j] = i * 3 + j + 1;
        return ret;
    }

    void printEquisatisfiableSatFormula() {
        // This solution prints a simple satisfiable formula
        // and passes about half of the tests.
        // Change this function to solve the problem.
        vector<vector<int> > idx = generate_idx();

        cout << 3 * numEdges + 4 * numVertices << " " << 3 * numVertices << endl;
        for(int i = 0; i < numVertices; ++i){
            cout << idx[i][0] << " " << idx[i][1] << " " << idx[i][2] << " 0" << endl;
            cout << -idx[i][0] << " " << -idx[i][1] << " 0" << endl;;
            cout << -idx[i][1] << " " << -idx[i][2] << " 0" << endl;;
            cout << -idx[i][2] << " " << -idx[i][0] << " 0" << endl;;
        }
        unordered_map<int, int> visited;
        for(auto p : edges){
            for(int j = 0; j < 3; ++j)
                cout << -idx[p.first][j] << " " << -idx[p.second][j] << " 0" << endl;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertGSMNetworkProblemToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        int from, to;
        cin >> from >> to;
        converter.edges.push_back({from-1, to-1});
        // converter.edges[from-1].push_back(to-1);
        // converter.edges[to-1].push_back(from-1);
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
