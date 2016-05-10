#include <iostream>
#include <cstring>
#include <cstdint>
#include <cstdio>

using namespace std;

const int64_t mod = 1000000007;

struct Node {
    int64_t sum;
    int64_t count;
    Node() : sum(0), count(0) {}
} dp[21][10][2][2][205];

int digits[21];
int64_t base[21];

Node dfs(int len, int digit, int sign, bool flip, bool limit, int mixed_sum, int64_t excepted)
{
    Node ret;
    if (!limit && dp[len][digit][sign > 0][flip][mixed_sum+100].count != -1)
        return dp[len][digit][sign > 0][flip][mixed_sum+100];
    if (len == 0) {
        if (mixed_sum == excepted)
            ret.count = 1;
        return ret;
    }

    for (int i = 0, iend = (limit ? digits[len-1] : 9); i <= iend; ++i) {
        Node tmp;
        if (flip || i != 0)
            tmp = dfs(len-1, i, -sign, true, limit && i == iend, mixed_sum + i * sign, excepted);
        else
            tmp = dfs(len-1, i, sign, false, limit && i == iend, mixed_sum + i * sign, excepted);
        ret.count += tmp.count;
        ret.sum = ((ret.sum + tmp.sum) % mod + ((i * tmp.count % mod) * base[len-1]) % mod ) % mod;
    }
    if (!limit)
        dp[len][digit][sign > 0][flip][mixed_sum+100] = ret;
    return ret;
}

int64_t solve(int64_t x, int64_t k)
{
    memset(dp, -1, sizeof(dp));
    int len = 0;
    while (x) {
        digits[len++] = x % 10;
        x /= 10;
    }
    int64_t ret = dfs(len, 0, 1, false, true, 0, k).sum;
    return ret;
}

int main(void)
{
    int64_t l, r, k, res;
    base[0] = 1;
    for (int i = 1; i < 21; ++i)
        base[i] = base[i-1] * 10 % mod;
    while (cin >> l >> r >> k) {
        if (l)
            res = (solve(r, k) - solve(l, k) + mod) % mod;
        else
            res = solve(r, k);
        cout << res << endl;
    }
    return 0;
}

