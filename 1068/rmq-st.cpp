#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int dp[1000001][32];

inline int log2n(int x)
{
    int ret = 0;
    while ((1 << ret) <= x)
        ++ret;
    return ret - 1;
}

int main(void)
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &dp[i][0]);
    }
    for (int j = 1, jend = log2n(n); j <= jend; ++j) {
        for (int i = 1; i+(1<<j)-1 <= n; ++i) {
            dp[i][j] = min(dp[i][j-1], dp[i+(1<<(j-1))][j-1]);
        }
    }
    int q;
    cin >> q;
    int l, r;
    for (int i = 0; i < q; ++i) {
        scanf("%d %d", &l, &r);
        int idx = log2n(r-l+1);
        printf("%d\n", min(dp[l][idx], dp[r-(1<<idx)+1][idx]));
    }
    return 0;
}
