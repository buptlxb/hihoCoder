#include <iostream>
#include <vector>
#include <numeric>
#include <stack>
#include <cassert>

using namespace std;

struct Edge {
    int v, next;
    Edge() : v(0), next(0) {}
};

int finds(int idx, vector<int> &trees)
{
    if (idx == trees[idx])
        return idx;
    return trees[idx] = finds(trees[idx], trees);
}

int unions(int a, int b, vector<int> &trees)
{
    int ea = finds(a, trees);
    int eb = finds(b, trees);
    trees[max(ea, eb)] = min(ea, eb);
}

void tarjan(int u, vector<int> &vertices, vector<Edge> &edges, vector<int> &ret, int &bridges)
{
    static vector<bool> visited(vertices.size());
    static vector<int> dfn(vertices.size()), low(dfn), parent(dfn);
    static stack<int> s;
    static int counter = 0;

    dfn[u] = low[u] = ++counter;
    visited[u] = true;
    s.push(u);

    for (int idx = vertices[u]; idx ; idx = edges[idx].next) {
        int v = edges[idx].v;
        if (!visited[v]) { // u-v is a tree edge
            parent[v] = u;
            tarjan(v, vertices, edges, ret, bridges);
            low[u] = min(low[u], low[v]);

            if (low[v] > dfn[u])
                ++bridges;
        } else { // u-v is a back edge
            if (v != parent[u])
                low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        // dfn[u] > dfn[parent[u]] => low[u] > dfn[parent[u]] => u-parent[u] is a bridge
        while (!s.empty() && s.top() != u) {
            unions(u, s.top(), ret);
            s.pop();
        }
        if (!s.empty())
            s.pop();
    }
}

int solve(vector<int> &vertices, vector<Edge> &edges, vector<int> &ret)
{
    int bridges = 1;
    iota(ret.begin(), ret.end(), 0);
    tarjan(1, vertices, edges, ret, bridges);
    return bridges;
}

int main(void)
{
    int n, m;
    cin >> n >> m;
    assert(n > 0);
    vector<int> vertices(n+1);
    vector<Edge> edges(m*2+2);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        
        int idx = i << 1;
        edges[idx].v = v;
        edges[idx].next = vertices[u];
        vertices[u] = idx;

        edges[idx+1].v = u;
        edges[idx+1].next = vertices[v];
        vertices[v] = idx+1;
    }
    vector<int> ret(vertices.size());
    int bridges = solve(vertices, edges, ret);
    cout << bridges << endl;
    cout << ret[1];
    for (int i = 2; i < ret.size(); ++i)
        cout << " " << finds(ret[i], ret);
    cout << endl;
    return 0;
}
