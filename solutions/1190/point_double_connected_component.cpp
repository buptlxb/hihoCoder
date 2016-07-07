#include <iostream>
#include <stack>
#include <vector>
#include <numeric>

using namespace std;

struct Edge {
    int v;
    int next;
    Edge() : v(0), next(0) {}
};

int finds(int idx, vector<int> &trees)
{
    if (idx == trees[idx])
        return idx;
    return trees[idx] = finds(trees[idx], trees);
}

void unions(int a, int b, vector<int> &trees)
{
    int ea = finds(a, trees), eb = finds(b, trees);
    trees[max(ea, eb)] = min(ea, eb);
}

void tarjan(int u, const vector<int> &headers, const vector<Edge> &edges, vector<int> &groups, int &dcc)
{
    static vector<int> dfn(headers.size()), low(dfn), parent(low);
    static vector<bool> pvisited(headers.size()), evisited(edges.size() >> 1);
    static stack<int> path;
    static int counter = 0;

    dfn[u] = low[u] = ++counter;
    pvisited[u] = true;
    for (int idx = headers[u]; idx; idx = edges[idx].next) {
        int v = edges[idx].v, e = idx >> 1;
        if (evisited[e])
            continue;
         path.push(e);
         evisited[e] = true;
        if (!pvisited[v]) {
            //path.push(e);
            parent[v] = u;
            tarjan(v, headers, edges, groups, dcc);
            low[u] = min(low[v], low[u]);
            if (low[v] >= dfn[u]) {
                ++dcc;
                int e2;
                do {
                    e2 = path.top();
                    unions(e, e2, groups);
                    path.pop();
                } while (!path.empty() && e != e2);
            }
        } else if (v != parent[u]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int solve(const vector<int> &headers, const vector<Edge> &edges, vector<int> &groups)
{
    iota(groups.begin(), groups.end(), 0);
    int dcc = 0;
    tarjan(1, headers, edges, groups, dcc);
    return dcc;
}

int main(void)
{
    int n, m;
    cin >> n >> m;
    vector<int> headers(n+1);
    vector<Edge> edges(m*2+2);
    for (int i = 1; i <= m; ++i) {
        int u, v, idx = i << 1;
        cin >> u >> v;
        edges[idx].v = v;
        edges[idx].next = headers[u];
        headers[u] = idx;
        ++idx;
        edges[idx].v = u;
        edges[idx].next = headers[v];
        headers[v] = idx;
    }
    vector<int> groups(m+1);
    int dcc = solve(headers, edges, groups);
    cout << dcc << endl;
    cout << groups[1];
    for (int i = 2; i <= m; ++i) 
        cout << " " << finds(groups[i], groups);
    cout << endl;
    return 0;
}
