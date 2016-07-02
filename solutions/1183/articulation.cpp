#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

#define N 20001
#define M 100001
struct Edge {
    int node;
    int next;
};

int graph[N], dfn[N], low[N], parent[N];
bool visit[N];
Edge edges[M<<1];
int n, m;

void dfs(int u, vector<int> &aps, vector<pair<int, int>> &bridges)
{
    static int counter = 0;
    int children = 0;
    visit[u] = true;
    dfn[u] = low[u] = ++counter;
    for (int i = graph[u]; i; i = edges[i].next) {
        int v = edges[i].node;
        if (!visit[v]) {
            ++children;
            parent[v] = u;
            dfs(v, aps, bridges);
            low[u] = min(low[u], low[v]);
            if (!parent[u] && children > 1)
                aps.push_back(u);
            if (parent[u] && low[v] >= dfn[u])
                aps.push_back(u);
            if (low[v] > dfn[u])
                bridges.push_back(make_pair(min(u, v), max(u, v)));
        } else if (v != parent[u]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void addEdge(int i, int u, int v)
{
    edges[i].node = v;
    edges[i].next = graph[u];
    graph[u] = i;
}

int main(void)
{
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        addEdge(i*2, u, v);
        addEdge(i*2+1, v, u);
    }
    vector<int> aps;
    vector<pair<int, int>> bridges;
    dfs(1, aps, bridges);
    sort(aps.begin(), aps.end());
    aps.erase(unique(aps.begin(), aps.end()), aps.end());
    sort(bridges.begin(), bridges.end());
    bridges.erase(unique(bridges.begin(), bridges.end()), bridges.end());
    if (aps.empty())
        cout << "Null" << endl;
    else {
        cout << aps.front();
        for (int i = 1; i < aps.size(); ++i)
            cout << " " << aps[i];
        cout << endl;
    }
    for (auto b : bridges)
        cout << b.first << " " << b.second << '\n';
    cout << flush;
    return 0;
}
