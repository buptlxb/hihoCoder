#include <iostream>
#include <cstring>
#include <cstddef>

using namespace std;

const int mod = 12357;

template<size_t N=8>
struct Matrix {
    int v[N][N];
    Matrix () {
        memset(v, 0, sizeof(v));
        for (int i = 0; i < N; ++i)
            v[i][i] = 1;
    }
    explicit Matrix (int x) { memset(v, 0, sizeof(v)); }
    size_t size() { return N; }
};

template<size_t N>
ostream & operator<< (ostream &os, const Matrix<N> &m)
{
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            cout << m.v[i][j] << " ";
        }
        cout << endl;
    }
    return os;
}

template<size_t N>
Matrix<N> mul(Matrix<N> a, Matrix<N> b)
{
    Matrix<N> ret(0);
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            for (size_t k = 0; k < N; ++k) {
                ret.v[i][j] = (ret.v[i][j] + a.v[i][k] * b.v[k][j]) % mod;
            }
        }
    }
    return ret;
}

template<size_t N>
Matrix<N> power(Matrix<N> m, int n)
{
    Matrix<N> ret, t = m;
    for (; n; n >>= 1) {
        if (n & 1)
            ret = mul(ret, t);
        t = mul(t, t);
    }
    return ret;
}

int solve(int n)
{
    if (n & 1)
        return 0;
    Matrix<8> m(0);
    m.v[0][7] = 1;
    m.v[1][6] = 1;
    m.v[2][5] = 1;
    m.v[3][4] = 1;
    m.v[3][7] = 1;
    m.v[4][3] = 1;
    m.v[5][2] = 1;
    m.v[6][1] = 1;
    m.v[6][7] = 1;
    m.v[7][0] = 1;
    m.v[7][3] = 1;
    m.v[7][6] = 1;
    return power(m, n).v[7][7];
}

int main(void)
{
    int n;
    while (cin >> n) {
        cout << solve(n) << endl;
    }
    return 0;
}
