#include <iostream>
#include <cassert>
#include <limits>

using namespace std;

struct Node{
    int id, val, num, lazy;
    unsigned long long total;
    Node *left, *right, *parent;
    Node(int i=0, int v=0) : id(i), val(v), num(1), lazy(0), total(v), left(0), right(0), parent(0) {}
} *root = nullptr;

void marking(Node *);
void send(Node *);
void update(Node *);
void left_rotate(Node *);
void right_rotate(Node *);
void splay(Node *, Node *);
Node *bst_insert(Node *, int, int);
void insert(int, int);
Node *find(int);
Node *find_prev(int);
Node *find_next(int);
void modify(int, int, int);
void erase(int, int);
void deleteTree(Node *);


void marking(Node *x, int lazy)
{
    assert(x);
    x->lazy += lazy;
    x->total += x->num * (long long)lazy;
    x->val += lazy;
}

void send(Node *x)
{
    assert(x);
    if (!x->lazy)
        return;
    if (x->left)
        marking(x->left, x->lazy);
    if (x->right)
        marking(x->right, x->lazy);
    x->lazy = 0;
    update(x);
}

void update(Node *x)
{
    x->total = x->val;
    x->num = 1;
    if (x->left) {
        x->total += x->left->total;
        x->num += x->left->num;
    }
    if (x->right) {
        x->total += x->right->total;
        x->num += x->right->num;
    }
}

void left_rotate(Node *x)
{
    assert(x);
    Node *p = x->parent;
    assert(p && p->right == x);

    send(p);
    send(x);

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

    update(p);
    update(x);
}

void right_rotate(Node *x)
{
    assert(x);
    Node *p = x->parent;
    assert(p && p->left == x);

    send(p);
    send(x);

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

    update(p);
    update(x);
}

void splay(Node *x, Node *y)
{
    assert(x);
    while (x->parent != y) {
        Node *p = x->parent;
        if (p->parent == y) {
            if (p->left == x)
                right_rotate(x);
            else
                left_rotate(x);
        } else {
            Node *g = p->parent;
            assert(g);
            if (p == g->left) {
                if (x == p->left) {
                    right_rotate(p);
                    right_rotate(x);
                } else {
                    left_rotate(x);
                    right_rotate(x);
                }
            } else {
                if (x == p->left) {
                    right_rotate(x);
                    left_rotate(x);
                } else {
                    left_rotate(p);
                    left_rotate(x);
                }
            }
        }
    }
}

Node *bst_insert(Node *x, int id, int val)
{
    assert(x);
    send(x);
    Node *ret;
    if (id < x->id) {
        if (!x->left) {
            ret = new Node(id, val);
            assert(ret);
            x->left = ret;
            ret->parent = x;
        } else
            ret = bst_insert(x->left, id, val);
    } else {
        if (!x->right) {
            ret = new Node(id, val);
            assert(ret);
            x->right = ret;
            ret->parent = x;
        } else
            ret = bst_insert(x->right, id, val);
    }
    update(x);
    return ret;
}

void insert(int id, int val)
{
    if (root)
        splay(bst_insert(root, id, val), nullptr);
    else
        root = new Node(id, val);
}

Node *find(int id)
{
    Node *cur = root;
    while (cur) {
        if (cur->id == id)
            return cur;
        else if (cur->id < id)
            cur = cur->right;
        else
            cur = cur->left;
    }
    return nullptr;
}

Node *find_prev(int id)
{
    Node *x = find(id);
    assert(x);
    splay(x, nullptr);
    Node *ret = x->left;
    assert(ret);
    while (ret->right)
        ret = ret->right;
    return ret;
}

Node *find_next(int id)
{
    Node *x = find(id);
    assert(x);
    splay(x, nullptr);
    Node *ret = x->right;
    assert(ret);
    while (ret->left)
        ret = ret->left;
    return ret;
}


void modify(int a, int b, int d)
{
    bool erase_a = false, erase_b = false;
    if (!find(a)) {
        erase_a = true;
        insert(a, 0);
    }
    if (!find(b)) {
        erase_b = true;
        insert(b, 0);
    }

    Node *prev = find_prev(a);
    Node *next = find_next(b);
    splay(prev, nullptr);
    splay(next, prev);

    marking(next->left, d);
    update(next);
    update(prev);

    if (erase_a)
        erase(a, a);
    if (erase_b)
        erase(b, b);
}

void erase(int a, int b)
{
    bool erase_a = false, erase_b = false;
    if (!find(a)) {
        erase_a = true;
        insert(a, 0);
    }
    if (!find(b)) {
        erase_b = true;
        insert(b, 0);
    }

    Node *prev = find_prev(a);
    Node *next = find_next(b);
    splay(prev, nullptr);
    splay(next, prev);

    assert(next->left);

    deleteTree(next->left);
    next->left = nullptr;
    update(next);
    update(prev);
}

unsigned long long query(int a, int b)
{
    bool erase_a = false, erase_b = false;
    if (!find(a)) {
        erase_a = true;
        insert(a, 0);
    }
    if (!find(b)) {
        erase_b = true;
        insert(b, 0);
    }

    Node *prev = find_prev(a);
    Node *next = find_next(b);
    splay(prev, nullptr);
    splay(next, prev);

    assert(next->left);
    unsigned long long ret = next->left->total;

    if (erase_a)
        erase(a, a);
    if (erase_b)
        erase(b, b);

    return ret;
}

void deleteTree(Node *x)
{
    if (x) {
        deleteTree(x->left);
        deleteTree(x->right);
        delete x;
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    char cmd;
    insert(numeric_limits<int>::min(), 0);
    insert(numeric_limits<int>::max(), 0);
    for (int i = 0; i < n; ++i) {
        cin >> cmd;
        if (cmd == 'I') {
            int id, val;
            cin >> id >> val;
            insert(id, val);
        } else if (cmd == 'Q') {
            int a, b;
            cin >> a >> b;
            cout << query(a, b) << '\n';
        } else if (cmd == 'M') {
            int a, b, d;
            cin >> a >> b >> d;
            modify(a, b, d);
        } else if (cmd == 'D') {
            int a, b;
            cin >> a >> b;
            erase(a, b);
        } else
            assert(0);
    }
    cout << flush;
    return 0;
}
