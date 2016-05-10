#include <iostream>
#include <vector>

using namespace std;

class SegmentTree {
    int size;
    vector<int> tree;
    void update(int index, int val, int root, int left, int right);
    int query(int start, int end, int root, int left, int right);
    int lson(int x) { return x << 1; }
    int rson(int x) { return (x << 1) | 1; }
public:
    SegmentTree(int n) : size(n), tree(n<<2) {}
    void update(int index, int val) {
        update(index, val, 1, 0, size-1);
    }
    int query(int start, int end) {
        return query(start, end, 1, 0, size-1);
    }
};
void SegmentTree::update(int index, int val, int root, int left, int right) {
    if (left == index && right == index)
        tree[root] = max(tree[root], val);
    else {
        int mid = left + (right-left)/2;
        if (index <= mid)
            update(index, val, lson(root), left, mid);
        else
            update(index, val, rson(root), mid+1, right);
        tree[root] = max(tree[lson(root)], tree[rson(root)]);
    }
}
int SegmentTree::query(int start, int end, int root, int left, int right) {
    if (start == left && end == right)
        return tree[root];
    else {
        int mid = left + (right-left)/2;
        if (end <= mid)
            return query(start, end, lson(root), left, mid);
        if (start > mid)
            return query(start, end, rson(root), mid+1, right);
        return max(query(start, mid, lson(root), left, mid), query(mid+1, end, rson(root), mid+1, right));
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> t(n), v(n);
    int size = 0;
    for (int i = 0; i < n; ++i) {
        cin >> t[i] >> v[i];
        size = max(size, t[i]);
    }
    SegmentTree st(size);
    for (int i = 0; i < n; ++i) {
        st.update(t[i]-1, v[i]);
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        int v = st.query(a-1, b-1);
        if (v)
            cout << v;
        else
            cout << "None";
        cout << '\n';
    }
    cout << flush;
    return 0;
}
