#include <iostream>
#include <map>
#include <cassert>
#include <vector>
#include <cstdio>

using namespace std;

vector<int> vertices[100005];
map<pair<int, int>, int> values;
map<pair<int, int>, long long> weights;
long long thd = 0;
int n, m;

void addEdge(int u, int v, int k)
{
    vertices[u].push_back(v);
    values[make_pair(u, v)] = k;
}

int dfs(int cur, int prev)
{
    int ret = 1;
    for (auto v : vertices[cur]) {
        if (v == prev)
            continue;
        int cnt = dfs(v, cur);
        ret += cnt;
        pair<int, int> p(cur, v);
        weights[p] = cnt * (n - (long long)cnt);
        thd += weights[p] * values[p];
    }
    return ret;
}

int main(void)
{
    cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        int u, v, k;
        cin >> u >> v >> k;
        vertices[u].push_back(v);
        vertices[v].push_back(u);
        pair<int, int> p(u, v);
        values[p] = k;
        p.first = v;
        p.second = u;
        values[p] = k;
    }
    thd = 0;
    dfs(1, -1);
    for (int i = 0; i < m; ++i) {
        string cmd;
        cin >> cmd;
        if (cmd == "QUERY")
            cout << thd << endl;
        else {
            int u, v, k;
            cin >> u >> v >> k;
            pair<int, int> e1(u, v);
            if (weights.find(e1) == weights.end()) {
                e1.first = v;
                e1.second = u;
            }
            thd += (long long)(k - values[e1]) * weights[e1];
            values[e1] = k;
        }
    }
    return 0;
}

