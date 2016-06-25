#include <iostream>
#include <cstdlib>
#include <cassert>

using namespace std;

struct TreapNode {
    int key, weight;
    TreapNode *parent, *left, *right;
    TreapNode(int k, int w) : key(k), weight(w), parent(nullptr), left(nullptr), right(nullptr) {}
};

class Treap {
    TreapNode *root;
    TreapNode *getNode(int x) { return new TreapNode(x, getWeight()); }
    void putNode(TreapNode *p) { free(p); }
    TreapNode *insert(TreapNode *root, int key) {
        if (key < root->key) {
            if (!root->left) {
                root->left = getNode(key);
                root->left->parent = root;
                return root->left;
            } else
                return insert(root->left, key);
        } else {
            if (!root->right) {
                root->right = getNode(key);
                root->right->parent = root;
                return root->right;
            } else
                return insert(root->right, key);
        }
    }
    void leftRotate(TreapNode *root) {
        TreapNode *right = root->right;
        right->parent = root->parent;
        if (root->parent) {
            if (root->parent->left == root)
                root->parent->left = right;
            else
                root->parent->right = right;
        }
        root->right = right->left;
        if (right->left)
            right->left->parent = root;
        right->left = root;
        root->parent = right;
        if (this->root == root)
            this->root = right;
    }
    void rightRotate(TreapNode *root) {
        TreapNode *left = root->left;
        left->parent = root->parent;
        if (root->parent) {
            if (root->parent->left == root)
                root->parent->left = left;
            else
                root->parent->right = left;
        }
        root->left = left->right;
        if (left->right)
            left->right->parent = root;
        left->right = root;
        root->parent = left;
        if (this->root == root)
            this->root = left;
    }
    void rotate(TreapNode *root) {
        while (root->parent) {
            TreapNode *parent = root->parent;
            if (parent->weight > root->weight) {
                if (parent->left == root)
                    rightRotate(parent);
                else
                    leftRotate(parent);
            } else
                break;
        }
    }
public:
    Treap(int x) : root(getNode(x)) {
        srand(time(nullptr));
    }
    void insert(int key) {
        rotate(insert(root, key));
    }
    TreapNode *find(int key) {
        TreapNode *cur = root;
        while (cur) {
            if (key == cur->key)
                break;
            else if (key < cur->key)
                cur = cur->left;
            else
                cur = cur->right;
        }
        return cur;
    }
    void erase(int key) {
        TreapNode *p = find(key);
        while (p->left && p->right) {
            TreapNode *c = p->left;
            if (c->weight > p->right->weight)
                c = p->right;
            if (c == p->left)
                rightRotate(p);
            else
                leftRotate(p);
        }
        TreapNode *parent = p->parent;
        if (p->left) {
            p->left->parent = parent;
            if (parent->left == p)
                parent->left = p->left;
            else
                parent->right = p->left;
        } else if (p->right) {
            p->right->parent = parent;
            if (parent->left == p)
                parent->left = p->right;
            else
                parent->right = p->right;
        } else {
            if (parent->left == p)
                parent->left = nullptr;
            else
                parent->right = nullptr;
        }
        putNode(p);
    }
    int upper_bound(int key) {
        assert(root);
        if (key <= minimum()->key)
            return minimum()->key;
        if (key >= maximum()->key)
            return maximum()->key;
        TreapNode *cur = root, *ret = nullptr;
        while (cur) {
            if (cur->key <= key) {
                ret = cur;
                cur = cur->right;
            } else {
                cur = cur->left;
            }
        }
        return ret->key;
    }
    TreapNode *minimum() {
        if (!root)
            return nullptr;
        TreapNode *cur = root;
        while (cur->left)
            cur = cur->left;
        return cur;
    }
    TreapNode *maximum() {
        if (!root)
            return nullptr;
        TreapNode *cur = root;
        while (cur->right)
            cur = cur->right;
        return cur;
    }


    int getWeight() { return rand(); }
};

int main(void)
{
    int n;
    cin >> n;
    char c;
    int k;
    cin >> c >> k;
    Treap t(k);
    for (int i = 1; i < n; ++i) {
        cin >> c >> k;
        if (c == 'I')
            t.insert(k);
        else
            cout << t.upper_bound(k) << endl;
    }
    return 0;
}
