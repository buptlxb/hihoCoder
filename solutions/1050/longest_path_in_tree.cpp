#include <iostream>
#include <vector>

using namespace std;

int dfs(int v, int p, const vector<int> &vertices, const vector<vector<int>> &edges, int &depth)
{
    int d = 0, r = v;
    for (int i = vertices[v]; i != -1; i = edges[i][1]) {
        if (edges[i][0] == p)
            continue;
        int t = dfs(edges[i][0], v, vertices, edges, d);
        if (d+1 > depth) {
            r = t;
            depth = d+1;
        }
    }
    return r;
}

int solve(const vector<int> &vertices, const vector<vector<int>> &edges)
{
    int depth = 0;
    int v1 = dfs(1, -1, vertices, edges, depth);
    int v2 = dfs(v1, -1, vertices, edges, depth);
    return depth;
}

int main(void)
{
    int n;
    while (cin >> n) {
        vector<vector<int>> edges(n<<1, vector<int>(2));
        vector<int> vertices(n+1, -1);
        int a, b;
        for (int i = 0; i < n; ++i) {
            cin >> a >> b;
            edges[i*2][0] = b;
            edges[i*2][1] = vertices[a];
            vertices[a] = i*2;
            edges[i*2+1][0] = a;
            edges[i*2+1][1] = vertices[b];
            vertices[b] = i*2+1;
        }
        cout << solve(vertices, edges) << endl;
    }
    return 0;
}
