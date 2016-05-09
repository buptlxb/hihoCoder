#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class SegmentTree {
    int size;
    vector<int> tree;
    void updateImpl(int index, int val, int root, int left, int right);
    int queryImpl(int first, int last, int root, int left, int right);
public:
    int lson(int idx) { return idx << 1; }
    int rson(int idx) { return (idx << 1) | 1; }
    explicit SegmentTree(int n) : size(n), tree(n*4) {}
    explicit SegmentTree(vector<int> & v) : size(v.size()), tree(v.size()*4) {
        for (int i = 0, iend = v.size(); i < iend; ++i)
            update(i, v[i]);
    }
    void update(int index, int val) {
        updateImpl(index, val, 1, 0, size-1);
    }
    int query(int first, int last) {
        return queryImpl(first, last, 1, 0, size-1);
    }
    friend ostream & operator<< (ostream &os, const SegmentTree &st);
};

void SegmentTree::updateImpl(int index, int val, int root, int left, int right)
{
    if (left == right)
        tree[root] = val;
    else {
        int mid = left + (right-left)/2;
        if (index <= mid)
            updateImpl(index, val, lson(root), left, mid);
        else
            updateImpl(index, val, rson(root), mid+1, right);
        tree[root] = min(tree[lson(root)], tree[rson(root)]);
    }
}

int SegmentTree::queryImpl(int first, int last, int root, int left, int right) {
    if (first == left && last == right)
        return tree[root];
    int mid = left + (right-left)/2;
    if (last <= mid)
        return queryImpl(first, last, lson(root), left, mid);
    if (first > mid)
        return queryImpl(first, last, rson(root), mid+1, right);
    return min(queryImpl(first, mid, lson(root), left, mid), queryImpl(mid+1, last, rson(root), mid+1, right));
}

ostream & operator<< (ostream &os, const SegmentTree &st) {
    for (auto x : st.tree)
        os << x << " ";
    return os;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> weights(n);
    for (int i = 0; i < n; ++i)
        cin >> weights[i];
    SegmentTree st(weights);
    int q, a, b, c;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> a >> b >> c;
        if (a)
            st.update(b-1, c);
        else
            cout << (st.query(b-1, c-1)) << "\n";
    }
    cout << flush;
    return 0;
}
