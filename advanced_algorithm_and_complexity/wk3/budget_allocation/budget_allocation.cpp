#include <ios>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

struct ConvertILPToSat {
    int numVar;
    vector< vector<int> > A;
    vector<int> b;
    vector<vector<int> > non_zero;

    ConvertILPToSat(int n, int m) : 
    numVar(m), 
    A(n, vector<int>(m)), 
    b(n), 
    non_zero(n)
    {}

    int check_one_by_one(stringstream &ss, int row){
        int num = non_zero[row].size();
        int ret = 0;
        if(num == 1){
            int x = A[row][non_zero[row][0]];
            // cout << x << " <= " << b[row] << endl;
            if(x > b[row]){
                ss << -(non_zero[row][0]+1) << " 0" << endl;
                ++ret;
            }
            if(0 > b[row]){
                ss << (non_zero[row][0]+1) << " 0" << endl;
                ++ret;
            }
        }
        else if(num == 2){
            int x = A[row][non_zero[row][0]];
            int y = A[row][non_zero[row][1]];
            if(0 > b[row]){
                ss << non_zero[row][0]+1 << " " << non_zero[row][1]+1 << " 0" << endl;    // !(!a and !b) -> a or b
                ++ret;
            }
            if(x > b[row]){
                ss << -(non_zero[row][0]+1) << " " << non_zero[row][1]+1 << " 0" << endl; // !(a and !b) -> !a or b
                ++ret;
            }
            if(y > b[row]){
                ss << non_zero[row][0]+1 << " " << -(non_zero[row][1]+1) << " 0" << endl; // !(!a and b) -> a or !b
                ++ret;
            }
            if(x + y > b[row]){
                ss << -(non_zero[row][0]+1) << " " << -(non_zero[row][1]+1) << " 0" << endl; // !(a and b) -> !a or !b
                ++ret;
            }
        }
        else if(num == 3){
            int x = A[row][non_zero[row][0]];
            int y = A[row][non_zero[row][1]];
            int z = A[row][non_zero[row][2]];
            if(0 > b[row]){
                ss << non_zero[row][0]+1 << " " << non_zero[row][1]+1 << " " << non_zero[row][2]+1 << " 0" << endl;    // !(!a and !b and !c) -> a or b or c
                ++ret;
            }
            if(x > b[row]){
                ss << -(non_zero[row][0]+1) << " " << non_zero[row][1]+1 << " " << non_zero[row][2]+1 << " 0" << endl; // !(a and !b and !c) -> !a or b or c
                ++ret;
            }
            if(y > b[row]){
                ss << (non_zero[row][0]+1) << " " << -(non_zero[row][1]+1) << " " << non_zero[row][2]+1 << " 0" << endl;
                ++ret;
            }
            if(z > b[row]){
              ss << (non_zero[row][0]+1) << " " << non_zero[row][1]+1 << " " << -(non_zero[row][2]+1) << " 0" << endl;
              ++ret;
            }
            if(x + y > b[row]){
              ss << -(non_zero[row][0]+1) << " " << -(non_zero[row][1]+1) << " " << non_zero[row][2]+1 << " 0" << endl; // !(a and b and !z) -> !a or !b or z
              ++ret;
            }
            if(y + z > b[row]){
              ss << (non_zero[row][0]+1) << " " << -(non_zero[row][1]+1) << " " << -(non_zero[row][2]+1) << " 0" << endl; //
              ++ret;
            }
            if(x + z > b[row]){
              ss << -(non_zero[row][0]+1) << " " << (non_zero[row][1]+1) << " " << -(non_zero[row][2]+1) << " 0" << endl; //
              ++ret;
            }
            if(x + y + z > b[row]){
              ss << -(non_zero[row][0]+1) << " " << -(non_zero[row][1]+1) << " " << -(non_zero[row][2]+1) << " 0" << endl; //// !(a and b and c) -> !a or !b or !c 
              ++ret;
            }
        }
        return ret;
    }

    void printEquisatisfiableSatFormula() {
        for(int i = 0; i < A.size(); ++i){
            if(non_zero[i].empty() and 0 > b[i]){
                cout << "2 1" << endl;
                cout << "1 0" << endl;
                cout << "-1 0" << endl;
                return;
            }
        }
        stringstream ss;
        int clauses = 0;
        for(int i = 0; i < A.size(); ++i){
            int temp = check_one_by_one(ss, i);
            clauses += temp;
        }
        if(clauses == 0){
            cout << "1 1" << endl;
            cout << "1 -1 0" << endl;
        }
        else{
            cout << clauses << " " << numVar << endl;
            cout << ss.str();
        }
        return;
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertILPToSat converter(n, m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> converter.A[i][j];
        if(converter.A[i][j] != 0)
            converter.non_zero[i].push_back(j);
      }
    }
    for (int i = 0; i < n; i++) {
      cin >> converter.b[i];
    }
    converter.printEquisatisfiableSatFormula();

    return 0;
}
