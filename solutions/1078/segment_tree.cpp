#include <iostream>
#include <vector>

using namespace std;

class SegmentTree {
    struct STNode {
        int sum, lazyTag;
        STNode() : sum(0), lazyTag(-1) {}
    };
    int size;
    vector<STNode> tree;
    void update(int index, int value, int root, int left, int right);
    void update(int first, int last, int value, int root, int left, int right);
    int query(int first, int last, int root, int left, int right);
    int lson(int idx) { return idx << 1; }
    int rson(int idx) { return (idx << 1) | 1; }
    void pushDown(int root, int left, int right) {
        if (tree[root].lazyTag != -1) {
            int mid = left + (right-left)/2;
            tree[lson(root)].lazyTag = tree[rson(root)].lazyTag = tree[root].lazyTag;
            tree[lson(root)].sum = tree[root].lazyTag * (mid-left+1);
            tree[rson(root)].sum = tree[root].lazyTag * (right-mid);
            tree[root].lazyTag = -1;
        }
    }
public:
    explicit SegmentTree(int n) : size(n), tree(n*4) {}
    explicit SegmentTree(const vector<int> &v) : size(v.size()), tree(v.size()*3) {
        for (int i = 0; i < v.size(); ++i)
            update(i, v[i]);
    }
    void update(int index, int value) {
        update(index, value, 1, 0, size-1);
    }
    int query(int first, int last) {
        return query(first, last, 1, 0, size-1);
    }
    void update(int first, int last, int value) {
        update(first, last, value, 1, 0, size-1);
    }
    friend ostream & operator<< (ostream &os, const SegmentTree &st);
};

void SegmentTree::update(int index, int value, int root, int left, int right) {
    if (left == right)
        tree[root].sum = value;
    else {
        int mid = left + (right-left)/2;
        if (index <= mid)
            update(index, value, lson(root), left, mid);
        else
            update(index, value, rson(root), mid+1, right);
        tree[root].sum = tree[lson(root)].sum + tree[rson(root)].sum;
    }
}
void SegmentTree::update(int first, int last, int value, int root, int left, int right) {
    if (first == left && last == right) {
        tree[root].sum = (right-left+1) * value;
        if (first != last)
            tree[root].lazyTag = value;
    } else {
        pushDown(root, left, right);
        int mid = left + (right-left)/2;
        if (last <= mid)
            update(first, last, value, lson(root), left, mid);
        else if (first > mid)
            update(first, last, value, rson(root), mid+1, right);
        else {
            update(first, mid, value, lson(root), left, mid);
            update(mid+1, last, value, rson(root), mid+1, right);
        }
        tree[root].sum = tree[lson(root)].sum + tree[rson(root)].sum;
    }
}
int SegmentTree::query(int first, int last, int root, int left, int right) {
    int mid = left + (right-left)/2;
    if (first == left && last == right)
        return tree[root].sum;
    pushDown(root, left, right);
    if (last <= mid)
        return query(first, last, lson(root), left, mid);
    if (first > mid)
        return query(first, last, rson(root), mid+1, right);
    return query(first, mid, lson(root), left, mid) + query(mid+1, last, rson(root), mid+1, right);
}

ostream & operator<< (ostream &os, const SegmentTree &st) {
    for (auto x : st.tree)
        cout << "(" << x.sum << ", " << x.lazyTag << ") ";
    return os;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, a;
    cin >> n;
    SegmentTree st(n);
    for (int i = 0; i < n; ++i) {
        cin >> a;
        st.update(i, a);
    }
    int q, b, c, d;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> a >> b >> c;
        if (a) {
            cin >> d;
            st.update(b-1, c-1, d);
        } else
            cout << st.query(b-1, c-1) << "\n";
    }
    cout << flush;
    return 0;
}
