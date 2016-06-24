#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

#define lson(x) (x<<1)
#define rson(x) ((x<<1)|1)

int tree[1600000];

void pushDown(int root, int b, int e)
{
    if (tree[root] && b + 1 < e) {
        tree[lson(root)] = tree[rson(root)] = tree[root];
        tree[root] = 0;
    }
}

void update(int l, int r, int val, int root, int b, int e)
{
    if (l == b && r == e)
        tree[root] = val;
    else {
        pushDown(root, b, e);
        int mid = b + (e - b) / 2;
        if (r <= mid)
            update(l, r, val, lson(root), b, mid);
        else if (l >= mid)
            update(l, r, val, rson(root), mid, e);
        else {
            update(l, mid, val, lson(root), b, mid);
            update(mid, r, val, rson(root), mid, e);
        }
    }
}

int query(int l, int r, int root, int b, int e, vector<int> &C)
{
    if (tree[root] == 1)
        return C[r] - C[l];
    if (tree[root] == -1 || l+1 >= r)
        return 0;
    int mid = b + (e - b) / 2;
    if (r <= mid)
        return query(l, r, lson(root), b, mid, C);
    if (l >= mid)
        return query(l, r, rson(root), mid, e, C);
    return query(l, mid, lson(root), b, mid, C) + query(mid, r, rson(root), mid, e, C);
}

int main(void)
{
    int n, m;
    cin >> n >> m;
    vector<int> A(n<<1), B(m<<1);
    for (int i = 0; i < n; ++i)
        cin >> A[i<<1]>> A[i*2+1];
    for (int j = 0; j < m; ++j)
        cin >> B[j<<1]>> B[j*2+1];
    vector<int> C(A);
    C.insert(C.end(), B.begin(), B.end());
    sort(C.begin(), C.end());
    C.erase(unique(C.begin(), C.end()), C.end());
    map<int, int> hash;
    for (int i = 0, iend = C.size(); i < iend; ++i) {
        hash[C[i]] = i;
    }
    int size = C.size();
    for (int i = 0; i < n; ++i)
        update(hash[A[i<<1]], hash[A[i*2+1]], 1, 1, 0, size-1);
    for (int j = 0; j < m; ++j)
        update(hash[B[j<<1]], hash[B[j*2+1]], -1, 1, 0, size-1);
    cout << query(0, size-1, 1, 0, size-1, C) << endl;
    return 0;
}
