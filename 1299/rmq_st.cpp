#include <iostream>
#include <vector>

using namespace std;

int dp[100005][30];

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    int size = 0;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int t, v;
        cin >> t >> v;
        dp[t][0] = max(v, dp[t][0]);
        size = max(size, t);
    }
    for (int j = 1; (1<<j) <= size; ++j) {
        for (int i = 1; i + (1<<j) <= size+1; ++i) {
            dp[i][j] = max(dp[i][j-1], dp[i+(1<<(j-1))][j-1]);
        }
    }
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        int j = 0;
        while (1<<j <= b-a+1) {
            ++j;
        }
        --j;
        int m = max(dp[a][j], dp[b-(1<<j)+1][j]);
        if (m)
            cout << m;
        else
            cout << "None";
        cout << '\n';
    }
    cout << flush;
    return 0;
}
