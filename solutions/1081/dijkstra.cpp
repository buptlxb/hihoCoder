#include <iostream> 
#include <limits>
#include <vector>
#include <cassert>

using namespace std;

long long int dijkstra(int s, int t, vector<vector<long long int>> &graph)
{
    vector<bool> visited(graph.size());
    visited[s] = true;
    while (true) {
        int v = 0;
        for (int i = 1; i < graph.size(); ++i) {
            if (visited[i])
                continue;
            if (graph[s][v] > graph[s][i])
                v = i;
        }
        if (v == t)
            return graph[s][v];
        visited[v] = true;
        for (int i = 1; i < graph.size(); ++i) {
            if (visited[i])
                continue;
            graph[s][i] = min(graph[s][i], graph[s][v] + graph[v][i]);
        }
    }
    assert(0);
}

int main(void)
{
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<vector<long long int>> graph(n+1, vector<long long int>(n+1, numeric_limits<int>::max()));
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a][b] = graph[b][a] = min<long long>(graph[a][b], c);
    }
    cout << dijkstra(s, t, graph) << endl;
    return 0;
}
