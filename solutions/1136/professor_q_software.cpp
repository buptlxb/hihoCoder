#include <iostream>
#include <map>
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
        vector<int> startups(n);
        vector<vector<int>> modules(n);
        map<int, set<int>> dict;
        queue<int> pending_signals;
        for (int i = 0; i < m; ++i) {
            int s;
            cin >> s;
            pending_signals.push(s);
        }
        for (int i = 0; i < n; ++i) {
            int start, s;
            int k;
            cin >> start >> k;
            for (int j = 0; j < k; ++j) {
                cin >> s;
                modules[i].push_back(s);
            }
            dict[start].insert(i);
        }
        while (!pending_signals.empty()) {
            int cur = pending_signals.front();
            pending_signals.pop();
            if (dict.find(cur) == dict.end())
                continue;
            for (auto idx : dict[cur]) {
                startups[idx] = (startups[idx] + 1) % MOD;
                for (auto &s : modules[idx])
                    pending_signals.push(s);
            }
        }
        cout << startups[0];
        for (int i = 1; i < n; ++i)
            cout << " " << startups[i];
        cout << '\n';
    }
    cout << flush;
    return 0;
}
