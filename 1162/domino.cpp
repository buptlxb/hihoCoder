#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

const int MOD = 12357;

struct Matrix {
    int value[1<<7][1<<7];
    int len;
    Matrix(int s, int val=0) : len(s) {
        memset(value, val, sizeof(value));
    }
    void normalize() { 
        memset(value, 0, sizeof(value));
        for (int i = 0; i < len; ++i)
            value[i][i] = 1;
    }
    int size() const { return len; }
    Matrix operator* (const Matrix &rhs) const {
        assert(len == rhs.size());
        Matrix ret(len);
        for (int i = 0; i < len; ++i)
            for (int j = 0; j < len; ++j)
                for (int k = 0; k < len; ++k)
                    ret.value[i][j] = (ret.value[i][j] + (unsigned long long)value[i][k] * rhs.value[k][j]) % MOD;
        return ret;
    }
};

ostream & operator<< (ostream &os, const Matrix &m)
{
    for (int i = 0, iend = m.size(); i < iend; ++i) {
        for (int j = 0, jend = m.size(); j < jend; ++j) {
            os << m.value[i][j] << " ";
        }
        cout << "\n";
    }
    return os;
}

Matrix & power_mod(Matrix &m, int exp) {
    Matrix t(m);
    m.normalize();
    while (exp) {
        if (exp & 1)
            m = m * t;
        exp >>= 1;
        t = t * t;
    }
    return m;
}

void dfs(int x, int y, int col, int k, Matrix &m)
{
    if (col == k) {
        m.value[y][x] = 1;
        return;
    }
    dfs(x << 1, (y << 1) + 1, col+1, k, m);
    dfs((x << 1) + 1, y << 1, col+1, k, m);
    if (col + 2 <= k)
        dfs((x << 2) + 3, (y << 2) + 3, col+2, k, m);
}

int solve(int k, int n)
{
    Matrix m(1<<k);
    dfs(0, 0, 0, k, m);
    power_mod(m, n);
    int idx = (1<<k) - 1;
    return m.value[idx][idx];
}

int main(void)
{
    int k, n;
    cin >> k >> n;
    cout << solve(k, n) << endl;
    return 0;
}
