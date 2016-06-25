#include <vector>
#include <iostream>

using namespace std;

void dfs(int start, vector<vector<int>> &nodes, vector<int> &path)
{
    for (int i = 0; i < nodes[start].size(); ++i) {
        int v = nodes[start][i];
        if (v != -1) {
            nodes[start][i] = -1;
            for (int j = 0; j < nodes[v].size(); ++j) {
                if (nodes[v][j] == start) {
                    nodes[v][j] = -1;
                    break;
                }
            }
            dfs(v, nodes, path);
        }
    }
    path.push_back(start);
}

int main(void)
{
    int n, m, u, v;
    cin >> n >> m;
    vector<vector<int>> nodes(n+1);
    while (m--) {
        cin >> u >> v;
        nodes[u].push_back(v);
        nodes[v].push_back(u);
    }
    vector<int> path;
    int start = 1;
    while (nodes[start].size() % 2 == 0 && start < nodes.size())
        ++start;
    if (start == nodes.size())
        start = u;
    dfs(start, nodes, path);
    for (auto p : path)
        cout << p << " ";
    cout << endl;
    return 0;
}
