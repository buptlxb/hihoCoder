#include <iostream>
#include <unordered_map>
#include <queue>
#include <set>

using namespace std;

#define MOD 142857

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> startups(n+1), indegrees(n+1);
        vector<vector<int>> modules(n+1);
        unordered_map<int, vector<int>> dict;
        modules[0].reserve(m);
        for (int i = 0; i < m; ++i) {
            int s;
            cin >> s;
            modules[0].push_back(s);
        }
        for (int i = 1; i <= n; ++i) {
            int start;
            int k;
            cin >> start >> k;
            while (k--) {
                int j;
                cin >> j;
                modules[i].push_back(j);
            }
            dict[start].push_back(i);
        }
        vector<vector<int>> graph(n+1);
        for (int i = 0; i <= n; ++i) {
            for (auto sig : modules[i]) {
                if (dict.find(sig) == dict.end())
                    continue;
                for (auto j : dict[sig]) {
                    graph[i].push_back(j);
                    ++indegrees[j];
                }
            }
        }
        queue<int> q;
        for (int i = 0; i <= n; ++i)
            if (indegrees[i] == 0)
                q.push(i);
        startups[0] = 1;
        while (!q.empty()) {
            int i = q.front();
            q.pop();
            for (auto j : graph[i]) {
                startups[j] += startups[i];
                if (--indegrees[j] == 0)
                    q.push(j);
            }
        }
        cout << startups[1];
        for (int i = 2; i <= n; ++i)
            cout << " " << startups[i];
        cout << '\n';
    }
    cout << flush;
    return 0;
}
