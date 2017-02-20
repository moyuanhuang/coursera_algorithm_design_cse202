#include <cstdio>
#include <stack>
#include <iostream>
#include <fstream>
// Splay tree implementation

using namespace std;
// Vertex of a splay tree
struct Vertex {
    long long key;
    // Sum of all the keys in the subtree - remember to update
    // it after each operation that changes the tree.
    long long sum;
    Vertex* left;
    Vertex* right;
    Vertex* parent;
    
    Vertex(long long key, long long sum, Vertex* left, Vertex* right, Vertex* parent)
    : key(key), sum(sum), left(left), right(right), parent(parent) {}
};

void update(Vertex* v) {
    if (v == NULL) return;
    v->sum = v->key + (v->left != NULL ? v->left->sum : 0ll) + (v->right != NULL ? v->right->sum : 0ll);
    if (v->left != NULL) {
        v->left->parent = v;
    }
    if (v->right != NULL) {
        v->right->parent = v;
    }
}

void small_rotation(Vertex* v) {
    Vertex* parent = v->parent;
    if (parent == NULL) {
        return;
    }
    Vertex* grandparent = v->parent->parent;
    if (parent->left == v) {
        Vertex* m = v->right;
        v->right = parent;
        parent->left = m;
    } else {
        Vertex* m = v->left;
        v->left = parent;
        parent->right = m;
    }
    update(parent);
    update(v);
    v->parent = grandparent;
    if (grandparent != NULL) {
        if (grandparent->left == parent) {
            grandparent->left = v;
        } else {
            grandparent->right = v;
        }
    }
}

void big_rotation(Vertex* v) {
    if (v->parent->left == v && v->parent->parent->left == v->parent) {
        // Zig-zig
        small_rotation(v->parent);
        small_rotation(v);
    } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
        // Zig-zig
        small_rotation(v->parent);
        small_rotation(v);
    } else {
        // Zig-zag
        small_rotation(v);
        small_rotation(v);
    }
}

// Makes splay of the given vertex and makes
// it the new root.
void splay(Vertex*& root, Vertex* v) {
    if (v == NULL) return;
    while (v->parent != NULL) {
        if (v->parent->parent == NULL) {
            small_rotation(v);
            break;
        }
        big_rotation(v);
    }
    root = v;
}

// Searches for the given key in the tree with the given root
// and calls splay for the deepest visited node after that.
// If found, returns a pointer to the node with the given key.
// Otherwise, returns a pointer to the node with the smallest
// bigger key (next value in the order).
// If the key is bigger than all keys in the tree,
// returns NULL.
Vertex* find(Vertex*& root, long long key) {
    Vertex* v = root;
    Vertex* last = root;
    Vertex* next = NULL;
    while (v != NULL) {
        if (v->key >= key && (next == NULL || v->key < next->key)) {
            next = v;
        }
        last = v;
        if (v->key == key) {
            break;
        }
        if (v->key < key) {
            v = v->right;
        } else {
            v = v->left;
        }
    }
    splay(root, last);
    return next;
}

void split(Vertex* root, long long key, Vertex*& left, Vertex*& right) {
    right = find(root, key);
    splay(root, right);
    if (right == NULL) {
        left = root;
        return;
    }
    left = right->left;
    right->left = NULL;
    if (left != NULL) {
        left->parent = NULL;
    }
    update(left);
    update(right);
}

Vertex* merge(Vertex* left, Vertex* right) {
    if (left == NULL) return right;
    if (right == NULL) return left;
    Vertex* min_right = right;
    while (min_right->left != NULL) {
        min_right = min_right->left;
    }
    splay(right, min_right);
    right->left = left;
    update(right);
    return right;
}

// Code that uses splay tree to solve the problem

Vertex* root = NULL;

void insert(long long x) {
    Vertex* left = NULL;
    Vertex* right = NULL;
    Vertex* new_vertex = NULL;
    split(root, x, left, right);
    if (right == NULL || right->key != x) {
        new_vertex = new Vertex(x, x, NULL, NULL, NULL);
    }
    root = merge(merge(left, new_vertex), right);
}

void erase(long long x) {
    // Implement erase yourself
    Vertex* next = find(root, x+1);

    Vertex* target = find(root, x);
    if(!target or target->key != x)  return;
    root = merge(root->left, root->right);
    if(root)
      root->parent = NULL;
    return;
}

bool find(long long x) {
    // Implement find yourself
    Vertex* res = find(root, x);
    return  res? (res->key == x): false;
}

long long sum(long long from, long long to) {
    Vertex* left = NULL;
    Vertex* middle = NULL;
    Vertex* right = NULL;
    split(root, from, left, middle);
    split(middle, to + 1, middle, right);
    long long ans = 0;
    // Complete the implementation of sum
    if(middle) ans = middle->sum;
    root = merge(merge(left, middle), right);
    if(root)  root->parent = NULL;
    return ans;
}

const int MODULO = 1000000001;

int main(){
    ofstream myfile ("result.txt");
    int n;
    scanf("%d", &n);
    long long last_sum_result = 0;
    for (int i = 0; i < n; i++) {
        char buffer[10];
        scanf("%s", buffer);
        char type = buffer[0];
        switch (type) {
            case '+' : {
                long long x;
                scanf("%lld", &x);
                insert((x + last_sum_result) % MODULO);
            } break;
            case '-' : {
                long long x;
                scanf("%lld", &x);
                erase((x + last_sum_result) % MODULO);
            } break;
            case '?' : {
                long long x;
                scanf("%lld", &x);
                bool res = find((x + last_sum_result) % MODULO);
                if(res){
                    printf("Found\n");
                    myfile << "Found\n";
                }
                else{
                    printf("Not found\n");
                    myfile << "Not found\n";
                }
            } break;
            case 's' : {
                long long l, r;
                scanf("%lld %lld", &l, &r);
                // cout << "scaned: " << l << " " << r <<endl;
                long long res = sum((l + last_sum_result) % MODULO, (r + last_sum_result) % MODULO);
                printf("%lld\n", res);
                myfile << res << endl;
                last_sum_result = int(res % MODULO);
            }
        }
    }
    return 0;
}
