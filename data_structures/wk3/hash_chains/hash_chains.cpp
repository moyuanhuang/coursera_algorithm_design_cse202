#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector< vector<string> > elems;

    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = 0; i < s.length(); i++)
            hash += fmod(s[i] * pow(multiplier, i), prime);
        hash = fmod(hash, prime);
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            // cout << "check" << endl;
            // use reverse order, because we append strings to the end
            for(int i = elems[query.ind].size()-1; i >= 0; --i)
                cout << elems[query.ind][i] << " ";
            std::cout << "\n";
        } else {
            size_t ind = hash_func(query.s);
            if (query.type == "find"){
                // cout << "find" << endl;
                for(int i = 0; i < elems[ind].size(); ++i)
                    if(elems[ind][i] == query.s){
                        cout << "yes" << endl;
                        return;
                    }
                cout << "no" << endl;
            }
            else if (query.type == "add"){
                // cout << "add" << endl;
                for(int i = 0; i < elems[ind].size(); ++i)
                    if(elems[ind][i] == query.s)  return;
                elems[ind].push_back(query.s);
            }
            else if (query.type == "del") {
                // cout << "del" << endl;
                for(int i = 0; i < elems[ind].size(); ++i)
                    if(elems[ind][i] == query.s){
                        elems[ind].erase(elems[ind].begin()+i);
                        return;
                    }
            }
        }
    }

    void processQueries() {
        elems.resize(bucket_count);
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
