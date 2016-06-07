#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool solve(vector<int> &degree, vector<vector<int>> &next)
{
    queue<int> q;
    for (int i = 0, iend = degree.size(); i < iend; ++i)
        if (degree[i] == 0)
            q.push(i);
    int num = 0;
    while (!q.empty()) {
        int idx = q.front();
        q.pop();
        ++num;
        for (auto x : next[idx]) {
            if (--degree[x] == 0)
                q.push(x);
        }
    }
    return num == degree.size();
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> degree(n);
        vector<vector<int>> next(n);
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            --a, --b;
            next[a].push_back(b);
            ++degree[b];
        }
        cout << (solve(degree, next) ? "Correct" : "Wrong") << '\n';
    }
    cout << flush;
    return 0;
}
