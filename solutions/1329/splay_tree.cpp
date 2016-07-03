#include <iostream>
#include <cassert>
#include <limits>

using namespace std;


struct TreeNode {
    TreeNode *left, *right, *parent;
    int val;
    TreeNode (int x) : left(nullptr), right(nullptr), parent(nullptr), val(x) {}
} *root;

void right_rotate(TreeNode *x)
{
    TreeNode *p = x->parent;
    x->parent = p->parent;
    if (p->parent) {
        if (p->parent->left == p)
            p->parent->left = x;
        else
            p->parent->right = x;
    } else
        root = x;
    p->left = x->right;
    if (x->right)
        x->right->parent = p;
    x->right = p;
    p->parent = x;
}

void left_rotate(TreeNode *x)
{
    TreeNode *p = x->parent;
    x->parent = p->parent;
    if (p->parent) {
        if (p->parent->left == p)
            p->parent->left = x;
        else
            p->parent->right = x;
    } else
        root = x;
    p->right = x->left;
    if (x->left)
        x->left->parent = p;
    x->left = p;
    p->parent = x;
}

void splay(TreeNode *x, TreeNode *y)
{
    if (x == nullptr)
        return;
    while (x->parent != y) {
        TreeNode *p = x->parent;
        if (p->parent == y) {   // zig
            if (p->left == x)
                right_rotate(x);
            else
                left_rotate(x);
        } else {
            TreeNode *g = p->parent;
            if (g->left == p) {
                if (p->left == x) {  // zig-zig
                    right_rotate(p);
                    right_rotate(x);
                } else {    // zig-zag
                    left_rotate(x);
                    right_rotate(x);
                }
            } else {
                if (p->right == x) {    // zig-zig
                    left_rotate(p);
                    left_rotate(x);
                } else {    // zig_zag
                    right_rotate(x);
                    left_rotate(x);
                }
            }
        }
    }
}

TreeNode *bst_insert(int key, TreeNode *p = root)
{
    if (p->val < key) {
        if (p->right)
            return bst_insert(key, p->right);
        p->right = new TreeNode(key);
        p->right->parent = p;
        return p->right;
    } else {
        if (p->left)
            return bst_insert(key, p->left);
        p->left = new TreeNode(key);
        p->left->parent = p;
        return p->left;
    }
}

void insert(int key)
{
    if (root) {
        TreeNode *x = bst_insert(key);
        splay(x, nullptr);
    } else
        root = new TreeNode(key);
}

TreeNode *bst_find(int key, TreeNode *p = root)
{
    if (!p || p->val == key)
        return p;
    if (p->val < key)
        return bst_find(key, p->right);
    return bst_find(key, p->left);
}

TreeNode *find(int key)
{
    TreeNode *x = bst_find(key);
    splay(x, nullptr);
    return x;
}

TreeNode *find_prev(int key)
{
    splay(find(key), nullptr);
    TreeNode *x = root->left;
    while (x->right)
        x = x->right;
    return x;
}

TreeNode *find_next(int key)
{
    splay(find(key), nullptr);
    TreeNode *x = root->right;
    while (x->left)
        x = x->left;
    return x;
}

void delete_tree(TreeNode *root)
{
    if (!root)
        return;
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}

void erase(int key)
{
    TreeNode *prev = find_prev(key);
    TreeNode *next = find_next(key);
    splay(prev, nullptr);
    splay(next, prev);
    delete next->left;
    next->left = nullptr;
}

void erase(int a, int b)
{
    if (!find(a))
        insert(a);
    if (!find(b))
        insert(b);
    TreeNode *prev = find_prev(a);
    TreeNode *next = find_next(b);
    splay(prev, nullptr);
    splay(next, prev);
    delete_tree(next->left);
    next->left = nullptr;
}

int query(int key)
{
    if (find(key))
        return key;
    insert(key);
    int ret = find_prev(key)->val;
    erase(key);
    return ret;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    char cmd;
    insert(numeric_limits<int>::min());
    insert(numeric_limits<int>::max());
    for (int i = 0; i < n; ++i) {
        cin >> cmd;
        if (cmd == 'I') {
            int k;
            cin >> k;
            insert(k);
        } else if (cmd == 'Q') {
            int k;
            cin >> k;
            cout << query(k) << '\n';
        } else if (cmd == 'D') {
            int a, b;
            cin >> a >> b;
            erase(a, b);
        } else
            assert(0);
    }
    return 0;
}
