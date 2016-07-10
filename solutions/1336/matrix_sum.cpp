#include <iostream>
#include <cassert>

using namespace std;

#define N 1005
#define MOD 1000000007

int bit[N][N];

int n;

inline int low_bit(int x)
{
    return x & -x;
}

void update(int x, int y, int value)
{
    for (int i = x+1; i <= n; i += low_bit(i)) {
        for (int j = y+1; j <= n; j += low_bit(j)) {
            bit[i][j] = (bit[i][j] + value) % MOD;
            bit[i][j] = (bit[i][j] + MOD) % MOD;
        }
    }
}

int sum(int x, int y)
{
    int ret = 0;
    for (int i = x+1; i > 0; i -= low_bit(i)) {
        for (int j = y+1; j > 0; j -= low_bit(j)) {
            ret = (ret + bit[i][j]) % MOD;
        }
    }
    return ret;
}

int sum(int x1, int y1, int x2, int y2)
{
    return (((sum(x2, y2)+sum(x1-1, y1-1))%MOD - (sum(x1-1, y2)+sum(x2, y1-1))%MOD) % MOD + MOD)%MOD;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m;
    cin >> n >> m;
    string cmd;
    for (int i = 0; i < m; ++i) {
        cin >> cmd;
        if (cmd[0] == 'A') {
            int x, y, value;
            cin >> x >> y >> value;
            update(x, y, value);
        } else if (cmd[0] == 'S') {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << sum(x1, y1, x2, y2) << '\n';
        } else
            assert(0);
    }
    cout << flush;
    return 0;
}
