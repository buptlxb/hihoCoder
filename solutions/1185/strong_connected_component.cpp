#include <iostream>
#include <vector>
#include <stack>
#include <numeric>
#include <queue>

using namespace std;

struct Edge {
    int v;
    int next;
    Edge (int a=0, int b=0) : v(a), next(b) {}
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

void tarjan(int u, vector<int> &headers, vector<Edge> &edges, vector<int> &ret, int &num)
{
    static vector<int> dfn(headers.size()), low(headers.size());
    static vector<bool> visited(headers.size()), path(headers.size());
    static stack<int> s;
    static int counter = 0;

    dfn[u] = low[u] = ++counter;
    visited[u] = path[u] = true;
    s.push(u);

    for (int idx = headers[u]; idx; idx = edges[idx].next) {
        int v = edges[idx].v;
        if (!visited[v]) {

            tarjan(v, headers, edges, ret, num);

            low[u] = min(low[u], low[v]);

            if (low[v] > dfn[u])
                ++num;

        } else if (path[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        while (!s.empty() && s.top() != u) {
            unions(u, s.top(), ret);
            path[s.top()] = false;
            s.pop();
        }
        if (!s.empty()) {
            path[s.top()] = false;
            s.pop();
        }
    }
}

int scc(vector<int> &headers, vector<Edge> &edges, vector<int> &ret)
{
    iota(ret.begin(), ret.end(), 0);
    int num = 1;
    tarjan(1, headers, edges, ret, num);
    return num;
}

int topology(int u, const vector<vector<int>> &graph, const vector<int> &gresses, vector<int> &degree, const vector<bool> &visited)
{
    queue<int> q;
    for (int i = 1; i < degree.size(); ++i)
        if (degree[i] == 0)
            q.push(i);
    vector<int> ret(gresses.size());
    int m = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (visited[u])
            ret[u] += gresses[u];
        m = max(ret[u], m);
        for (auto v : graph[u]) {
            ret[v] = max(ret[v], ret[u]);
            if (--degree[v] == 0)
                q.push(v);
        }
    }
    return m;
}

int dfs(int u, vector<vector<int>> &graph, vector<int> &gresses)
{
    int ret = 0;
    for (auto v : graph[u])
        ret = max(ret, dfs(v, graph, gresses));
    return ret + gresses[u];
}

void dfs(int u, vector<vector<int>> &graph, vector<bool> &visited)
{
    visited[u] = true;
    for (auto v : graph[u])
        dfs(v, graph, visited);
}

int main(void)
{
    int n, m;
    cin >> n >> m;
    vector<int> headers(n+1), gresses(n+1);
    vector<Edge> edges(m+1);

    for (int i = 1; i <= n; ++i)
        cin >> gresses[i];
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;

        edges[i].v = v;
        edges[i].next = headers[u];
        headers[u] = i;

    }
    vector<int> ret(n+1);
    int nums = scc(headers, edges, ret);

    vector<vector<int>> graph(n+1);
    vector<int> cgresses(n+1), degree(n+1);

    for (int i = 1; i <= n; ++i) {
        int u = finds(i, ret);
        cgresses[u] += gresses[i];
        for (int j = headers[i]; j; j = edges[j].next) {
            int v = finds(edges[j].v, ret);
            if (u == v)
                continue;
            graph[u].push_back(v);
            ++degree[v];
        }
    }

    vector<bool> visited(n+1);
    dfs(1, graph, visited);
    cout << topology(1, graph, cgresses, degree, visited) << endl;
    //cout << dfs(1, graph, cgresses) << endl;
    return 0;
}
