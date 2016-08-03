#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

int solve(const vector<int> &levels, int m, int s, int t)
{
    vector<vector<int>> dp(levels.size()+1, vector<int>(m+1, m+1));
    dp[0].assign(m+1, 0);
    for (int i = 1; i < dp.size(); ++i) {
        int right = (levels[i-1] + s - 1) / s;
        for (int j = 0; j <= right; ++j) {
            int remain = levels[i-1] - s * j;
            int wrong = remain > 0 ? (remain + t - 1) / t : 0;
            for (int k = 0; k+j+wrong <= m; ++k)
                dp[i][k+j+wrong] = min(dp[i][k+j+wrong], dp[i-1][k]+j);
        }
    }
    return *min_element(dp.back().begin(), dp.back().end());
}

int main(void)
{
    int q;
    cin >> q;
    while (q--) {
        int n, m, s, t;
        cin >> n >> m >> s >> t;
        vector<int> levels(n);
        for (int i = 0; i < n; ++i)
            cin >> levels[i];
        int res = solve(levels, m, s, t);
        if (res > m)
            cout << "No" << endl;
        else
            cout << res << '\n';
    }
    cout << flush;
    return 0;
}
