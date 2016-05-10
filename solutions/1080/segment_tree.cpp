#include <iostream>
#include <vector>

using namespace std;

class SegmentTree {
public:
    enum class LazyTag { NONE, SET, CUR };
private:
    struct STNode {
        LazyTag tag;
        int sum;
        int val;
        STNode() : tag(SegmentTree::LazyTag::NONE), sum(0), val(0) {}
    };
    int size;
    vector<STNode> tree;
    int lson(int x) { return x << 1; }
    int rson(int x) { return (x << 1) | 1;}
    void update(LazyTag tag, int start, int end, int val, int root, int left, int right);
    void updateNode(LazyTag tag, int val, int root, int left, int right);
    int query(int start, int end, int root, int left, int right);
    void pushDown(int root, int left, int right) {
        if (tree[root].tag != LazyTag::NONE) {
            int mid = left + (right-left)/2;
            updateNode(tree[root].tag, tree[root].val, lson(root), left, mid);
            updateNode(tree[root].tag, tree[root].val, rson(root), mid+1, right);
            tree[root].tag = LazyTag::NONE;
        }
    }
public:
    SegmentTree(int n) : size(n), tree(n<<2) {}
    void update(LazyTag tag, int start, int end, int val) {
        update(tag, start, end, val, 1, 0, size-1);
    }
    int query() { return query(0, size-1); }
    int query(int start, int end) { return query(start, end, 1, 0, size-1); }
};
void SegmentTree::updateNode(LazyTag tag, int val, int root, int left, int right) {
    if (tree[root].tag == LazyTag::NONE) {
        tree[root].tag = tag;
        tree[root].val = val;
        if (tag == LazyTag::SET)
            tree[root].sum = (right-left+1) * val;
        else /* if (tag == LazyTag::CUR) */
            tree[root].sum += (right-left+1) * val;
    } else if (tree[root].tag == LazyTag::SET) {
        if (tag == LazyTag::SET) {
            tree[root].val = val;
            tree[root].sum = (right-left+1) * val;
        } else /* if (tag == LazyTag::CUR) */ {
            tree[root].val += val;
            tree[root].sum += (right-left+1) * val;
        }
    } else /* if (tree[root].tag == LazyTag::CUR) */ {
        if (tag == LazyTag::SET) {
            tree[root].tag = tag;
            tree[root].val = val;
            tree[root].sum = (right-left+1) * val;
        } else /* if (tag == LazyTag::CUR) */ {
            tree[root].val += val;
            tree[root].sum += (right-left+1) * val;
        }
    }
}
void SegmentTree::update(LazyTag tag, int start, int end, int val, int root, int left, int right) {
    if (start == left && end == right) {
        updateNode(tag, val, root, left, right);
        return;
    }
    pushDown(root, left, right);
    int mid = left + (right-left)/2;
    if (end <= mid)
        update(tag, start, end, val, lson(root), left, mid);
    else if (start > mid)
        update(tag, start, end, val, rson(root), mid+1, right);
    else {
        update(tag, start, mid, val, lson(root), left, mid);
        update(tag, mid+1, end, val, rson(root), mid+1, right);
    }
    tree[root].sum = tree[lson(root)].sum + tree[rson(root)].sum;
}
int SegmentTree::query(int start, int end, int root, int left, int right) {
    if (start == left && end == right)
        return tree[root].sum;
    pushDown(root, left, right);
    int mid = left + (right-left)/2;
    if (end <= mid)
        return query(start, end, lson(root), left, mid);
    if (start > mid)
        return query(start, end, rson(root), mid+1, right);
    return query(start, mid, lson(root), left, mid) + query(mid+1, end, rson(root), mid+1, right);
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    SegmentTree st(n+1);
    for (int i = 0; i <= n; ++i) {
        int p; cin >> p;
        st.update(SegmentTree::LazyTag::SET, i, i, p);
    }
    for (int i = 0; i < m; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        st.update(a ? SegmentTree::LazyTag::SET : SegmentTree::LazyTag::CUR, b, c, d);
        cout << st.query() << "\n";
    }
    cout << flush;
    return 0;
}
