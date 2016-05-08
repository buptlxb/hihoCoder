#include <iostream>
#include <vector>

using namespace std;

void dfs(int idx, int m, vector<int> &value, vector<vector<int>> &tree, vector<vector<int>> &dp)
{
    dp[idx][1] = value[idx];
    for (auto x : tree[idx])
        dfs(x, m, value, tree, dp);
    for (auto x : tree[idx]) {
        for (int j = m; j >= 2; --j) {
            for (int k = 1; k < j; ++k) {
                dp[idx][j] = max(dp[idx][j], dp[idx][j-k] + dp[x][k]);
            }
        }
    }
}

int solve(vector<int> &value, vector<vector<int>> &tree, int m, vector<vector<int>> &dp)
{
    dfs(1, m, value, tree, dp);
    return dp[1][m];
}

int main(void)
{
    int n, m;
    cin >> n >> m;
    vector<int> value(n+1);
    vector<vector<int>> tree(n+1), dp(n+1, vector<int>(m+1));
    for (int i = 1; i <= n; ++i)
        cin >> value[i];
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        if (a < b)
            tree[a].push_back(b);
        else
            tree[b].push_back(a);
    }
    cout << solve(value, tree, m, dp) << endl;
    return 0;
}
