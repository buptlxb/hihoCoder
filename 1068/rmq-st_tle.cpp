#include <iostream>
#include <vector>

using namespace std;

int log2n(int x)
{
    while (x & (x-1))
        x &= x-1;
    int ret = 0;
    for ( ; x; x >>=1)
        ++ret;
    return ret;
}

int query(vector<vector<int>> &dp, int start, int idx)
{
    if (start >= dp.size())
        return 10001;
    if (!dp[start][idx])
        dp[start][idx] = min(query(dp, start, idx-1), query(dp, start+(1<<(idx-1)), idx-1));
    return dp[start][idx];
}

int solve(vector<vector<int>> &dp, int left, int right)
{
    int idx = log2n(right-left+1) - 1;
    return min(query(dp, left, idx), query(dp, right-(1<<(idx-1))+1, idx));
}

int main(void)
{
    int n;
    cin >> n;
    vector<vector<int>> dp(n+1, vector<int>(log2n(n)));
    for (int i = 1; i <= n; ++i) {
        cin >> dp[i][0];
    }
    int q;
    cin >> q;
    int l, r;
    for (int i = 0; i < q; ++i) {
        cin >> l >> r;
        cout << solve(dp, l, r) << endl;
    }
    return 0;
}
