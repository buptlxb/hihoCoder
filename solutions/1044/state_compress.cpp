#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

inline int bitcount(int x)
{
    int ret = 0;
    for (; x; x &= x-1)
        ++ret;
    return ret;
}

int solve(const vector<int> &w, int m, int q)
{
    --m;
    vector<vector<int>> dp(w.size(), vector<int>(1 << m));
    --m;
    for (vector<int>::size_type i = 0, iend = dp.size(); i != iend; ++i) {
        for (vector<int>::size_type j = 0, jend = dp[i].size(); j < jend; ++j) {
            int t = i == 0 ? 0 : dp[i-1][j];
            vector<int>::size_type idx = (j>>1) | (1 << m);
            if (bitcount(j) < q)
                dp[i][idx] = max(t + w[i], dp[i][idx]);
            dp[i][j>>1] = max(t, dp[i][j>>1]);
        }
    }
    return *max_element(dp.back().begin(), dp.back().end());
}

int main(void)
{
    int n, m, q;
    while (cin >> n >> m >> q) {
        vector<int> w(n);
        for (int i = 0; i < n; ++i)
            cin >> w[i];
        cout << solve(w, m, q) << endl;
    }
    return 0;
}
