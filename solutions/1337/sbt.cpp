#include <iostream>
#include <cstddef>
#include <cassert>

using namespace std;

#define GET_VALUE(ptr, member, dfl) (ptr ? ptr->member : dfl)
#define SIZE(ptr) GET_VALUE(ptr, size, 0)

struct SBTNode {
    size_t size;
    SBTNode *left;
    SBTNode *right;
    int key;
    SBTNode (int k) : size(1), left(nullptr), right(nullptr), key(k) {}
} *root = nullptr;

inline SBTNode *get_node(int key)
{
    return new SBTNode(key);
}

inline void put_node(SBTNode *t)
{
    delete t;
}

inline void left_rotate(SBTNode * &t)
{
    if (!t) return;

    SBTNode *r = t->right;
    t->right = r->left;
    r->left = t;
    r->size = t->size;
    t->size = SIZE(t->left) + SIZE(t->right) + 1;
    t = r;
}

inline void right_rotate(SBTNode * &t)
{
    if (!t) return;

    SBTNode *l = t->left;
    t->left = l->right;
    l->right = t;
    l->size = t->size;
    t->size = SIZE(t->left) + SIZE(t->right) + 1;
    t = l;
}

void maintain(SBTNode *&t, bool check_right)
{
    if (!t) return;

    if (!check_right) {
        if (!t->left) return;
        if (SIZE(t->left->left) > SIZE(t->right)) {
            right_rotate(t);
        } else if (SIZE(t->left->right) > SIZE(t->right)) {
            left_rotate(t->left);
            right_rotate(t);
        } else
            return;
    } else {
        if (!t->right) return;
        if (SIZE(t->right->left) > SIZE(t->left)) {
            right_rotate(t->right);
            left_rotate(t);
        } else if (SIZE(t->right->right) > SIZE(t->left)) {
            left_rotate(t);
        } else
            return;
    }

    maintain(t->left, false);
    maintain(t->right, true);
    maintain(t, false);
    maintain(t, true);
}

void insert(SBTNode *&t, int key)
{
    if (!t)
        t = get_node(key);
    else {
        t->size += 1;
        if (t->key > key)
            insert(t->left, key);
        else
            insert(t->right, key);
        maintain(t, key >= t->key);
    }
}

int erase(SBTNode * &t, int key)
{
    assert(t);
    t->size -= 1;
    int ret;
    if (t->key == key || (t->key > key && !t->left) || (t->key <= key && !t->right)) {
        ret = t->key;
        if (t->left && t->right) {
            t->key = erase(t->left, t->key+1);
        } else {
            SBTNode *d = t;
            if (t->left) {
                t = t->left;
            } else {
                t = t->right;
            }
            put_node(d);
        }
    } else {
        if (t->key > key)
            return erase(t->left, key);
        else
            return erase(t->right, key);
    }
    return ret;
}

SBTNode *find(const SBTNode *t, int key)
{
    if (!t || t->key == key)
        return const_cast<SBTNode *>(t);
    if (key < t->key)
        return find(t->left, key);
    else
        return find(t->right, key);
}

int nth_element(const SBTNode *t, int k)
{
    assert(t);
    int n = SIZE(t->left) + 1;
    if (n == k)
        return t->key;
    if (k < n)
        return nth_element(t->left, k);
    else
        return nth_element(t->right, k-n);
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        char c; int k;
        cin >> c >> k;
        if (c == 'I')
            insert(root, k);
        else if (c == 'Q')
            cout << nth_element(root, k) << '\n';
        else if (c == 'D')
            erase(root, k);
        else
            assert(0);
    }
    cout << flush;
    return 0;
}
