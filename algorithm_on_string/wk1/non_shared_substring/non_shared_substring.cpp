#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <assert.h>
#include <climits>

using namespace std;

const int LETTERS = 6;
const char L_TYPE = 'l';
const char R_TYPE = 'r';
const char LR_TYPE = 'm';

struct TreeNode{
    int start;
    int length;
    int num_edges = 0;
    char type;
    TreeNode* edges[LETTERS]; // only AGCT$# 6 character
    TreeNode(int s, int l){
        start = s;
        length = l;
        type = 0;
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
    break_node->num_edges++;
    parent->edges[i] = break_node;
    return break_node;
}

TreeNode* build_trie(const string &text){
    int text_len = text.length();
    TreeNode* root = new TreeNode(0, 0);
    for(int i = 0; i < text_len; ++i){
        TreeNode* cur_node = root;
        int i_new = i;
        while(true){
            // for(int i_new = i; i_new < text_len; ++i_new){
            int edge_idx = to_idx(text[i_new]);
            if(cur_node->edges[edge_idx] == nullptr){
                TreeNode* new_node = new TreeNode(i_new, text_len - i_new);
                cur_node->edges[edge_idx] = new_node;
                cur_node->num_edges++;
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
                        break_node->num_edges++;
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

char annotate_tree(const string &text, TreeNode* &root){
    if(root->num_edges == 0){
        for(size_t i = root->start; i < root->start + root->length; ++i)
            if(text[i] == '#'){
                root->type = L_TYPE;
                return L_TYPE;
            }
        root->type = R_TYPE;
        return R_TYPE;
    }
    bool l = false, r = false;
    for(size_t i = 0; i < LETTERS; ++i){
        if(!root->edges[i]) continue;
        char type = annotate_tree(text, root->edges[i]);
        if(type == LR_TYPE){
            l = true;
            r = true;
        }
        else if(type == L_TYPE)  l = true;
        else r = true;
    }
    if(l and r) root->type = LR_TYPE;
    else if(l)  root->type = L_TYPE;
    else    root->type = R_TYPE;
    return root->type;
}

string find_min(const string &text, TreeNode* root, string cur){
    if(root->num_edges == 0){
        if(text[root->start] == '#'){
            // cout << "entered wrong function!" << endl;
            return "";  //"#CAA$", won't happend if code is right
        }
        else{
            cur.push_back(text[root->start]);
            // cout << "returning" << cur << endl;
            return cur; //"C#CAA$"
        }
    }
    if(root->type == L_TYPE){
        cur.push_back(text[root->start]);
        // cout << "returning" << cur << endl;
        return cur;
    }
    else if(root->type == LR_TYPE){
        cur += text.substr(root->start, root->length);
        string shorttest = "";
        int min_length = INT_MAX;
        for(size_t i = 0; i < LETTERS - 2; ++i){
            if(!root->edges[i] or root->edges[i]->type == R_TYPE)   continue;
            string tmp = find_min(text, root->edges[i], cur);
            // cout << "this time " << tmp << endl;
            if(tmp.length() != 0 and tmp.length() < min_length){
                // cout << "shortest changed " << tmp << endl;
                shorttest = tmp;
                min_length = tmp.length();
            }
        }
        return shorttest;
    }
    // cout << "entering wrong code" << endl;
    return "";
}

string  solve (string p, string q)
{
    if(p.length() == 0) return "";
    string text = p + "#" + q + "$";
    TreeNode* root = build_trie(text);
    annotate_tree(text, root);
    string result = find_min(text, root, "");
    return result;
}

int main (void)
{
    string p;
    cin >> p;
    string q;
    cin >> q;
    
    string ans = solve (p, q);
    
    cout << ans << endl;
    
    return 0;
}
