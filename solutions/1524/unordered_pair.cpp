#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct TreeNode{
    int key;
    int children_count;
    TreeNode *left;
    TreeNode *right;
    TreeNode (int k) : key(k), children_count(1), left(nullptr), right(nullptr) { }
};

TreeNode * GetTreeNode(int key) {
    return new TreeNode(key);
}

void PutTreeNode(TreeNode *ptr) {
    if (ptr)
        free(ptr);
}

inline int GetChildrenCount(TreeNode *ptr) {
    return ptr ? ptr->children_count : 0;
}

uint64_t Insert(TreeNode * &root, int key) {
    uint64_t result = 0;

    do {
        if (root == nullptr) {
            root = GetTreeNode(key);
            break;
        }

        if (key < root->key) {
            result = Insert(root->left, key) + GetChildrenCount(root->right) + 1;
        } else {
            result = Insert(root->right, key);
        }

        root->children_count += 1;
    } while (0);

    return result;
}

void Destroy(TreeNode *root) {
    do {
        if (!root)
            break;
        Destroy(root->left);
        Destroy(root->right);
        PutTreeNode(root);
    } while (0);
}

void Print(const TreeNode *root) {
    if (!root)
        return;
    Print(root->left);
    cout << root->key << ":" << root->children_count << endl;
    Print(root->right);
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    uint64_t unordered_pair_count = 0;
    TreeNode *root = nullptr;
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        unordered_pair_count += Insert(root, x);
    }
    cout << unordered_pair_count << endl;
    return 0;
}
