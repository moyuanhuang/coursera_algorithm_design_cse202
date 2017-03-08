#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <assert.h>

using namespace std;

const int LETTERS = 6;

struct TreeNode{
    int start;
    int length;
    TreeNode* edges[LETTERS]; // only AGCT$# 6 character
    TreeNode(int s, int l){
        start = s;
        length = l;
        fill(edges, edges + LETTERS, nullptr);
    }
};

size_t to_idx(char letter){
    switch (letter)
    {
        case 'A': return 0; break;
        case 'C': return 1; break;
        case 'G': return 2; break;
        case 'T': return 3; break;
        case '$': return 4; break;
        case '#': return 5; break;
        default: cout << letter << endl; assert (false); return -1;
    }
}

TreeNode* break_edge(const string &text, TreeNode* &parent, int i,  int length){
    TreeNode* child_node = parent->edges[i];
    TreeNode* break_node = new TreeNode(child_node->start, length);
    child_node->start += length;
    child_node->length -= length;
    break_node->edges[to_idx(text[child_node->start])] = child_node;
    parent->edges[i] = break_node;
    return break_node;
}

TreeNode* build_trie(const string &text){
    int text_len = text.length();
    TreeNode* root = new TreeNode(-1, 0);
    for(int i = 0; i < text_len; ++i){
        TreeNode* cur_node = root;
        int i_new = i;
        while(true){
            // for(int i_new = i; i_new < text_len; ++i_new){
            int edge_idx = to_idx(text[i_new]);
            if(cur_node->edges[edge_idx] == nullptr){
                TreeNode* new_node = new TreeNode(i_new, text_len - i_new);
                cur_node->edges[edge_idx] = new_node;
                break;
            }
            else{
                int start = cur_node->edges[edge_idx]->start;
                int len_ori = cur_node->edges[edge_idx]->length;
                int len_new = text_len - i_new;
                bool added = false;
                for(int i_origin = start; i_new < text_len and i_origin < start + len_ori; ++i_new, ++i_origin){
                    if(text[i_origin] != text[i_new]){
                        TreeNode* break_node = break_edge(text, cur_node, edge_idx, i_origin - start);
                        break_node->edges[to_idx(text[i_new])] = new TreeNode(i_new, text_len - i_new);
                        added = true;
                        break;
                    }
                }
                if(added or len_ori == len_new) break;
                if(len_ori < len_new) cur_node = cur_node->edges[edge_idx];
                else{
                    assert (false); return nullptr;
                }
            }
        }
    }
    return root;
}

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding
// substrings of the text) in any order.
vector<string> ComputeSuffixTreeEdges(const string& text) {
    vector<string> result;
    TreeNode* root = build_trie(text);
    // Implement this function yourself
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        TreeNode* tmp = q.front(); q.pop();
        for(int i = 0; i < LETTERS; ++i){
            if(!tmp->edges[i])  continue;
            q.push(tmp->edges[i]);
            string edge = text.substr(tmp->edges[i]->start, tmp->edges[i]->length);
            result.push_back(edge);
        }
    }
    return result;
}

int main() {
    string text;
    cin >> text;
//    TreeNode* test_root = build_trie(text);
    vector<string> edges = ComputeSuffixTreeEdges(text);
    for (int i = 0; i < edges.size(); ++i) {
        cout << edges[i] << endl;
    }
    return 0;
}
