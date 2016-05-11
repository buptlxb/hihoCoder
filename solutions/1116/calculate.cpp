#include <iostream>
#include <vector>

using namespace std;

const int MOD = 10007;

class SegmentTree {
    struct STNode {
        int sum;
        int prefix;
        int suffix;
        int product;
        STNode() : sum(0), prefix(0), suffix(0), product(0) {}
    };
    int size;
    vector<STNode> tree;
    void update(int index, int val, int root, int left, int right);
    int lson(int x) { return x << 1; }
    int rson(int x) { return (x << 1) | 1; }
public:
    SegmentTree(int n) : size(n), tree(n<<2) {}
    void update(int index, int val) { update(index, val, 1, 0, size-1); }
    int query() { return tree[1].sum; }
};
void SegmentTree::update(int index, int val, int root, int left, int right) {
    if (left == index && left == right) {
        tree[root].sum = tree[root].prefix = tree[root].suffix = tree[root].product = val % MOD;
    } else {
        int mid = left + (right-left)/2;
        if (index <= mid)
            update(index, val, lson(root), left, mid);
        else
            update(index, val, rson(root), mid+1, right);
        tree[root].sum = (tree[lson(root)].sum + tree[rson(root)].sum + tree[lson(root)].suffix * tree[rson(root)].prefix) % MOD;
        tree[root].prefix = (tree[lson(root)].prefix + tree[lson(root)].product * tree[rson(root)].prefix) % MOD;
        tree[root].suffix = (tree[rson(root)].suffix + tree[lson(root)].suffix * tree[rson(root)].product) % MOD;
        tree[root].product = (tree[lson(root)].product * tree[rson(root)].product) % MOD;
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    SegmentTree st(n);
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        st.update(a-1, b);
        cout << st.query() << '\n';
    }
    cout << flush;
    return 0;
}
