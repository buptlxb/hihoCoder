#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

struct Matrix {
    int v[2][2];
    Matrix() {
        v[0][0] = 1;
        v[0][1] = 0;
        v[1][0] = 0;
        v[1][1] = 1;
    }
};

const int mod = 19999997;

Matrix mul(Matrix a, Matrix b)
{
    Matrix ret;
    ret.v[0][0] = ((uint64_t)a.v[0][0]*b.v[0][0] + (uint64_t)a.v[0][1]*b.v[1][0]) % mod;
    ret.v[0][1] = ((uint64_t)a.v[0][0]*b.v[0][1] + (uint64_t)a.v[0][1]*b.v[1][1]) % mod;
    ret.v[1][0] = ((uint64_t)a.v[1][0]*b.v[0][0] + (uint64_t)a.v[1][1]*b.v[1][0]) % mod;
    ret.v[1][1] = ((uint64_t)a.v[1][0]*b.v[0][1] + (uint64_t)a.v[1][1]*b.v[1][1]) % mod;
    return ret;
}

Matrix power(Matrix m, int n)
{
    Matrix ret, t = m;
    for (; n; n >>= 1) {
        if (n & 1)
            ret = mul(ret, t);
        t = mul(t, t);
    }
    return ret;
}

int solve(int n)
{
    Matrix m;
    m.v[0][0] = 0;
    m.v[0][1] = 1;
    m.v[1][0] = 1;
    m.v[1][1] = 1;
    return power(m, n).v[1][1];
}

int main(void)
{
    int n;
    while (cin >> n) {
        cout << solve(n) << endl;
    }
    return 0;
}
