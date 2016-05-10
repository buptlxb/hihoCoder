#include <iostream>
#include <map>

using namespace std;

string solve(map<string, string> tree, string a, string b)
{
    map<string, bool> m;
    while (!a.empty()) {
        m[a] = true;
        a = tree[a];
    }
    while (!b.empty() && !m[b])
        b = tree[b];
    if (b.empty())
        return "-1";
    return b;
}

int main(void)
{
    int n;
    cin >> n;
    map<string, string> tree;
    string a, b;
    for (int i = 0; i < n; ++i) {
        cin >> a >> b;
        tree[b] = a;
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        cout << solve(tree, a, b) << endl;
    }
    return 0;
}
