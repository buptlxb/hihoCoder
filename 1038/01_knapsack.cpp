#include <iostream>
#include <vector>

using namespace std;

int solve(const vector<int> &need, const vector<int> &value, int m)
{
    vector<int> dp(m+1);
    for (vector<int>::size_type i = 0, iend = need.size(); i < iend; ++i) {
        for (int j = m; j >= need[i]; --j) {
            dp[j] = max(dp[j], dp[j-need[i]] + value[i]);
        }
    }
    return dp[m];
}

int main(void)
{
    int n, m;
    while (cin >> n >> m) {
        vector <int> need(n), value(n);
        for (int i = 0; i < n; ++i)
            cin >> need[i] >> value[i];
        cout << solve(need, value, m) << endl;
    }
    return 0;
}
