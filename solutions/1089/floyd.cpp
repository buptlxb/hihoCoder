#include <iostream>
#include <vector>
#include <limits>

using namespace std;

void floyd(vector<vector<long long>> &graph)
{
    for (int k = 1; k < graph.size(); ++k) {
        for (int i = 1; i < graph.size(); ++i) {
            for (int j = 1; j < graph.size(); ++j) {
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }
}

int main(void)
{
    int n, m;
    cin >> n >> m;
    vector<vector<long long>> graph(n+1, vector<long long>(n+1, numeric_limits<int>::max()));
    for (int i = 1; i <= n; ++i)
        graph[i][i] = 0;
    for (int i = 1; i <= m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a][b] = graph[b][a] = min<long long>(graph[a][b], c);
    }
    floyd(graph);
    for (int i = 1; i < graph.size(); ++i) {
        cout << graph[i][1];
        for (int j = 2; j < graph.size(); ++j) {
            cout << " " << graph[i][j];
        }
        cout << '\n';
    }
    cout << flush;
    return 0;
}
