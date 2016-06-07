#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Node {
    int val, m;
} tree[800000];

inline int lson(int root) {
    return root << 1;
}

inline int rson(int root) {
    return (root << 1) | 1;
}

void pushDown(int root, int left, int right) {
    if (tree[root].val) {
        tree[lson(root)].val += tree[root].val;
        tree[rson(root)].val += tree[root].val;
        tree[lson(root)].m += tree[root].val;
        tree[rson(root)].m += tree[root].val;
        tree[root].val = 0;
    }
}

void pushUp(int root) {
    tree[root].m = max(tree[lson(root)].m, tree[rson(root)].m);
}

void update(int start, int end, int root, int left, int right)
{
    if (left + 1 == right) {
        tree[root].m += 1;
        tree[root].val = 0;
    } else if (start == left && end == right) {
        ++tree[root].val;
        ++tree[root].m;
    } else {
        pushDown(root, left, right);
        int mid = left + (right-left)/2;
        if (end <= mid)
            update(start, end, lson(root), left, mid);
        else if (start >= mid)
            update(start, end, rson(root), mid, right);
        else {
            update(start, mid, lson(root), left, mid);
            update(mid, end, rson(root), mid, right);
        }
        pushUp(root);
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> s(n), e(n);
    vector<int> nums;
    nums.reserve(n*2);
    for (int i = 0; i < n; ++i) {
        cin >> s[i] >> e[i];
        nums.push_back(s[i]);
        nums.push_back(e[i]);
    }
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    map<int, int> dict;
    for (int i = 0; i < nums.size(); ++i) {
        dict[nums[i]] = i;
    }
    for (int i = 0; i < n; ++i)
        update(dict[s[i]], dict[e[i]], 1, 0, nums.size()-1);
    cout << tree[1].m << endl;
    return 0;
}
