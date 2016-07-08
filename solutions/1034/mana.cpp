#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

class SegmentTree {
    struct STNode {
        uint64_t sum;
        int m, r, t;
        STNode() : sum(0), m(0), r(0), t(0) {}
    };
    int size;
    vector<STNode> tree;
    int lson(int x) { return x << 1; }
    int rson(int x) { return (x << 1) | 1; }
    uint64_t query(int start, int end, int root, int left, int right);
    void recover(int start, int end, int time, int root, int left, int right);
    void clean(int start, int end, int time, int root, int left, int right);
    void init(int index, int s, int m, int r, int root, int left, int right);
public:
    SegmentTree (int n) : size(n), tree(n<<2) {}
    uint64_t query(int start, int end) { return query(start, end, 1, 0, size-1); }
    void recover(int start, int end, int time) { recover(start, end, time, 1, 0, size-1); }
    void clean(int start, int end, int time) { clean(start, end, time, 1, 0, size-1); }
    void init(int index, int s, int m, int r) { init(index, s, m, r, 1, 0, size-1); }
};

uint64_t SegmentTree::query(int start, int end, int root, int left, int right) {
    if (start == left && end == right)
        return tree[root].sum;
    int mid = left + (right-left)/2;
    if (end <= mid)
        return query(start, end, lson(root), left, mid);
    if (start > mid)
        return query(start, end, rson(root), mid+1, right);
    return query(start, mid, lson(root), left, mid) + query(mid+1, end, rson(root), mid+1, right);
}
void SegmentTree::recover(int start, int end, int time, int root, int left, int right) {
    if (start == left && end == right && left == right) {
        uint64_t tmp = tree[root].sum + (time - tree[root].t) * tree[root].r;
        tree[root].sum = min(tmp, (uint64_t)tree[root].m);
    } else {
        int mid = left + (right-left)/2;
        if (end <= mid)
            recover(start, end, time, lson(root), left, mid);
        else if (start > mid)
            recover(start, end, time, rson(root), mid+1, right);
        else {
            recover(start, mid, time, lson(root), left, mid);
            recover(mid+1, end, time, rson(root), mid+1, right);
        }
        tree[root].sum = tree[lson(root)].sum + tree[rson(root)].sum;
    }
}
void SegmentTree::clean(int start, int end, int time, int root, int left, int right) {
    if (start == left && end == right && left == right) {
        tree[root].sum = 0;
        tree[root].t = time;
    } else {
        int mid = left + (right-left)/2;
        if (end <= mid)
            clean(start, end, time, lson(root), left, mid);
        else if (start > mid)
            clean(start, end, time, rson(root), mid+1, right);
        else {
            clean(start, mid, time, lson(root), left, mid);
            clean(mid+1, end, time, rson(root), mid+1, right);
        }
        tree[root].sum = tree[lson(root)].sum + tree[rson(root)].sum;
    }
}
void SegmentTree::init(int index, int s, int m, int r, int root, int left, int right) {
    if (left == right && left == index) {
        tree[root].sum = s;
        tree[root].m = m;
        tree[root].r = r;
    } else {
        int mid = left + (right-left)/2;
        if (index <= mid)
            init(index, s, m, r, lson(root), left, mid);
        else
            init(index, s, m, r, rson(root), mid+1, right);
        tree[root].sum = tree[lson(root)].sum + tree[rson(root)].sum;
    }
}


int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    SegmentTree st(n);
    for (int i = 0; i < n; ++i) {
        int s, m, r;
        cin >> s >> m >> r;
        st.init(i, s, m, r);
    }
    int m;
    cin >> m;
    uint64_t sum = 0;
    for (int i = 0; i < m; ++i) {
        int t, l, r;
        cin >> t >> l >> r;
        --l; --r;
        st.recover(l, r, t);
        sum += st.query(l, r);
        st.clean(l, r, t);
    }
    cout << sum << endl;
    return 0;
}
