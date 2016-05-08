#include <iostream>
#include <vector>
#include <map>
#include <cstdio>

using namespace std;

vector<string> persons;

int nhash(string a)
{
    static map<string, int> dict;
    if (dict.find(a) == dict.end()) {
        dict[a] = persons.size();
        persons.push_back(a);
    }
    return dict[a];
}

int log2n(int x)
{
    int ret = 0;
    while (1 << ret <= x)
        ++ret;
    return ret - 1;
}

void tree2array(map<int, vector<int>> &tree, int root, vector<int> &array, map<int, int> &indices)
{
    array.push_back(root);
    for (auto child : tree[root]) {
        tree2array(tree, child, array, indices);
        array.push_back(root);
    }
    indices[root] = array.size();
    array.push_back(root);
}

void rmq_init(vector<vector<int>> &dp, vector<int> array)
{
    for (vector<int>::size_type i = 0; i < dp.size(); ++i)
        dp[i][0] = array[i];
    for (vector<int>::size_type j = 1; j < dp[0].size(); ++j) {
        for (vector<int>::size_type i = 0; i + (1<<j) - 1 < dp.size(); ++i) {
            dp[i][j] = min(dp[i][j-1], dp[i+(1<<(j-1))][j-1]);
        }
    }
}

int main(void)
{
    int n;
    string f, s;
    map<int, vector<int>> tree;
    int root = 0;
    cin >> n;
    while (n--) {
        cin >> f >> s;
        int fi = nhash(f);
        int si = nhash(s);
        tree[fi].push_back(si);
    }
    vector<int> array;
    map<int, int> indices;
    tree2array(tree, root, array, indices);

    vector<vector<int>> dp(array.size(), vector<int>(log2n(array.size())+1));
    rmq_init(dp, array);

    int q;
    cin >> q;
    while (q--) {
        cin >> f >> s;
        int fi = indices[nhash(f)];
        int si = indices[nhash(s)];
        if (fi < si) {
            int idx = log2n(si-fi+1);
            cout << persons[min(dp[fi][idx], dp[si-(1<<idx)+1][idx])] << endl;
        } else {
            int idx = log2n(fi-si+1);
            cout << persons[min(dp[si][idx], dp[fi-(1<<idx)+1][idx])] << endl;
        }
    }
    return 0;
}
