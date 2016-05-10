#include <iostream>
#include <vector>

using namespace std;

int solve(const vector<int> &need, const vector<int> &value, int m)
{
    vector<vector<int>> dp(2, vector<int>(m+1));
    for (vector<int>::size_type i = 0, iend = need.size(); i < iend; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (j < need[i])
                dp[1][j] = dp[0][j];
            else
                dp[1][j] = max(dp[0][j], dp[1][j-need[i]]+value[i]);
        }
        dp[1].swap(dp[0]);
    }
    return dp[0][m];
}

int main(void)
{
    int n, m;
    while (cin >> n >> m) {
        vector<int> need(n), value(n);
        for (int i = 0; i < n; ++i)
            cin >> need[i] >> value[i];
        cout << solve(need, value, m) << endl;
    }
    return 0;
}
