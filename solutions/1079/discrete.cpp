#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

class SegmentTree {
    int size;
    vector<int> tree;
    void update(int start, int end, int tag, int root, int left, int right);
    int query(int start, int end, int root, int idx);
    void pushDown(int root) {
        if (tree[root]) {
            tree[lson(root)] = tree[rson(root)] = tree[root];
            tree[root] = 0;
        }
    }
    int lson(int x) { return x << 1; }
    int rson(int x) { return (x << 1) | 1; }
public:
    SegmentTree(int n) : size(n), tree(n<<2) {}
    void update(int start, int end, int tag) {
        update(start, end, tag, 1, 0, size-1);
    }
    int query(int idx) { return query(0, size-1, 1, idx); }
};

void SegmentTree::update(int start, int end, int tag, int root, int left, int right) {
    if (start == left && end == right)
        tree[root] = tag;
    else {
        pushDown(root);
        int mid = left + (right-left)/2;
        if (end <= mid)
            update(start, end, tag, lson(root), left, mid);
        else if (start >= mid)
            update(start, end, tag, rson(root), mid, right);
        else {
            update(start, mid, tag, lson(root), left, mid);
            update(mid, end, tag, rson(root), mid, right);
        }
    }
}
int SegmentTree::query(int start, int end, int root, int idx) {
    while (!tree[root] && start+1 < end) {
        int mid = start + (end-start)/2;
        if (idx >= mid) {
            start = mid;
            root = rson(root);
        } else {
            end = mid;
            root = lson(root);
        }
    }
    return tree[root];
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, l;
    cin >> n >> l;
    vector<pair<int, int>> ranges(n);
    vector<int> nums;
    nums.reserve(n<<1);
    for (int i = 0; i < n; ++i) {
        cin >> ranges[i].first >> ranges[i].second;
        nums.push_back(ranges[i].first);
        nums.push_back(ranges[i].second);
    }
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    sort(nums.begin(), nums.end());
    map<int, int> dict;
    for (int i = 0; i < nums.size(); ++i)
        dict[nums[i]] = i;
    SegmentTree st(nums.size());
    for (int i = 0; i < ranges.size(); ++i) {
        st.update(dict[ranges[i].first], dict[ranges[i].second], i+1);
    }
    set<int> ret;
    ret.insert(0);
    for (int i = 1; i < nums.size(); ++i)
        ret.insert(st.query(i-1));
    cout << ret.size()-1 << endl;
    return 0;
}
