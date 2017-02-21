#include <cstdio>
#include <string>
#include <iostream>
#include <stack>

using namespace std;

struct Vertex
{
    char key;
    long long sum;  // number of nodes below the node (include itself)
    Vertex* left;
    Vertex* right;
    Vertex* parent;

    Vertex(char key, long long sum, Vertex* left, Vertex* right, Vertex* parent) :
            key(key), sum(sum), left(left), right(right), parent(parent)
    {
    }
};

class Rope
{
    string s;
    Vertex* root;
    public:
    Rope(const string &s) :
            s(s)
    {
        root = NULL;
        for (int w = 0; w < s.length(); w++)
        {
            Vertex* next = new Vertex(s[w], 1ll, NULL, NULL, NULL);
            root = merge(root, next);
        }
    }

    ~Rope()
    {
        free_space(root);
    }

    void free_space(Vertex* root)
    {
        if (root != NULL)
        {
            if (root->left != NULL)
            {
                free_space(root->left);
            }
            if (root->right != NULL)
            {
                free_space(root->right);
            }
            delete root;
        }
    }
    void update(Vertex* v)
    {
        if (v == NULL)
            return;
        v->sum = 1 + (v->left != NULL ? v->left->sum : 0ll)
                + (v->right != NULL ? v->right->sum : 0ll);
        if (v->left != NULL)
        {
            v->left->parent = v;
        }
        if (v->right != NULL)
        {
            v->right->parent = v;
        }
    }

    void small_rotation(Vertex* v)
    {
        Vertex* parent = v->parent;
        if (parent == NULL)
        {
            return;
        }
        Vertex* grandparent = v->parent->parent;
        if (parent->left == v)
        {
            Vertex* m = v->right;
            v->right = parent;
            parent->left = m;
        }
        else
        {
            Vertex* m = v->left;
            v->left = parent;
            parent->right = m;
        }
        update(parent);
        update(v);
        v->parent = grandparent;
        if (grandparent != NULL)
        {
            if (grandparent->left == parent)
            {
                grandparent->left = v;
            }
            else
            {
                grandparent->right = v;
            }
        }
    }

    void big_rotation(Vertex* v)
    {
        if (v->parent->left == v && v->parent->parent->left == v->parent)
        {
            // Zig-zig
            small_rotation(v->parent);
            small_rotation(v);
        }
        else if (v->parent->right == v && v->parent->parent->right == v->parent)
        {
            // Zig-zig
            small_rotation(v->parent);
            small_rotation(v);
        }
        else
        {
            // Zig-zag
            small_rotation(v);
            small_rotation(v);
        }
    }

    // Makes splay of the given vertex and makes
    // it the new root.
    void splay(Vertex*& root, Vertex* v)
    {
        if (v == NULL)
            return;
        while (v->parent != NULL)
        {
            if (v->parent->parent == NULL)
            {
                small_rotation(v);
                break;
            }
            big_rotation(v);
        }
        root = v;
    }

    // Searches for the node which has 'leftNum' number of nodes
    // in the left side(including itself) in the tree with the given root
    // and calls splay for the deepest visited node after that.
    // If found, returns a pointer to that node
    // Otherwise (only in case leftNum is bigger than the total
    // number of the nodes in the tree), returns NULL

    Vertex* find(Vertex*& root, int leftNum)
    {
        Vertex* v = root;

        while(v!=NULL)
        {
            long long s = (v->left != NULL) ? v->left->sum : 0ll;
            if (leftNum == (s + 1))
            {
                break;
            }
            else if (leftNum < (s + 1))
            {
                v = v->left;
            }
            else if (leftNum > (s + 1))
            {
                v = v->right;
                leftNum = leftNum - s - 1;
            }
        }
        splay(root, v);
        return v;
    }

    void split(Vertex* root, int key, Vertex*& left, Vertex*& right)
    {
        right = find(root, key);
        //splay(root, right);

        if (right == NULL)
        {
            left = root;
            return;
        }

        left = right->left;

        right->left = NULL;

        if (left != NULL)
        {
            left->parent = NULL;
        }

        update(left);
        update(right);
    }

    Vertex* merge(Vertex* left, Vertex* right)
    {
        if (left == NULL)
            return right;
        if (right == NULL)
            return left;
        Vertex* min_right = right;
        while (min_right->left != NULL)
        {
            min_right = min_right->left;
        }
        splay(right, min_right);
        right->left = left;
        update(right);
        return right;
    }


    void insert(Vertex*& root, int k, Vertex*& subString)
    {
        Vertex* left = NULL;
        Vertex* right = NULL;
        split(root, k, left, right);
        root = merge(merge(left, subString), right);
    }

    string traversal_in_order(Vertex* root)
    {
        string s = "";
        if (!root)  return s;
        stack<Vertex*> st;
        Vertex* p = root;
        while (p != NULL){
            st.push(p);
            p = p->left;
        }
        while (!st.empty()){
            p = st.top();
            s.push_back(p->key);
            st.pop();
            p = p->right;
            while (p != NULL)
            {
                st.push(p);
                p = p->left;
            }

        }
        return s;
    }

    void process(int i, int j, int k)
    {
        if (i > j)
            swap(i, j);
        Vertex* left = NULL;
        Vertex* right = NULL;
        Vertex* middle = NULL;
        split(root, i + 1, left, middle);
        split(middle, j - i + 2, middle, right);
        root = merge(left, right);
        insert(root, k + 1, middle);
    }

    string result()
    {
        s.clear();
        s = traversal_in_order(root);
        return s;
    }
};

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::string s;
    std::cin >> s;
    Rope rope(s);
    int actions;
    std::cin >> actions;
    for (int action_index = 0; action_index < actions; ++action_index)
    {
        int i, j, k;
        std::cin >> i >> j >> k;
        rope.process(i, j, k);
    }
    cout << rope.result() << endl;

    return 0;
}
