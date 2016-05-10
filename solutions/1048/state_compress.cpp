#include <iostream>
#include <vector>

using namespace std;

const int mod = 1000000007;

inline int bit(int a, int idx)
{
    return (a >> idx) & 0x1;
}

int dfs(int a, int b, int s, vector<vector<vector<int>>> &cache)
{
    if (a >= cache.size() || b >= cache[a].size() || s >= cache[a][b].size())
        return 1;
    if (cache[a][b][s] != -1)
        return cache[a][b][s];
    int m = cache[a].size();
    if (bit(s, b)) {
        if (b+1 == m) {
            cache[a][b][s] = dfs(a+1, 0, s>>m, cache);
        } else {
            cache[a][b][s] = dfs(a, b+1, s, cache);
        }
    } else {
        if (b+1 < m && !bit(s, b+1))
            cache[a][b][s] = dfs(a, b, s | (1<<b) | (1<<(b+1)), cache) % mod;
        else
            cache[a][b][s] = 0;
        if (a+1 < cache.size() && !bit(s, b+m))
            cache[a][b][s] = (cache[a][b][s] + dfs(a, b, s | (1<<b) | (1<<(b+m)), cache)) % mod;
    }
    return cache[a][b][s];
}

int solve(int n, int m)
{
    if (n * m % 2 != 0)
        return 0;
    vector<vector<vector<int>>> cache(n, vector<vector<int>>(m, vector<int>(1<<(2*m), -1)));
    return dfs(0, 0, 0, cache);
}

int main(void)
{
    int n, m;
    while (cin >> n >> m) {
        cout << solve(n, m) << endl;
    }
    return 0;
}
