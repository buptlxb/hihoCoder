#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

double solve(int n, int m)
{
    vector<vector<double>> dp(n+1, vector<double>(max(m, 6)+1));
    for (int k = 1; k <= 6; ++k) {
        dp[1][k] = 1.0 / 6;
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 1*i; j <= min(m, 6*i); ++j) {
            for (int k = 1; k <= 6 && j-k >= 1; ++k) {
                dp[i][j] += dp[i-1][j-k];
            }
            dp[i][j] /= 6;
        }
    }
    return dp[n][m];
}

int main(void)
{
    int n, m;
    cin >> n >> m;
    cout << fixed << setprecision(2);
    cout << 100 * solve(n, m) << endl;
    return 0;
}
