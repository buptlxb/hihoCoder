#include <iostream>
#include <cstring>

using namespace std;

#define MOD 1000000007

template <long long N>
struct Matrix {
    long long val[N][N];
    void normalize() {
        memset(val, 0, sizeof(val));
        for (long long i = 0; i < N; ++i)
            val[i][i] = 1;
    }
};

template <long long N>
Matrix<N> operator* (const Matrix<N> &lhs, const Matrix<N> &rhs)
{
    Matrix<N> m;
    for (long long i = 0; i < N; ++i) {
        for (long long j = 0; j < N; ++j) {
            m.val[i][j] = 0;
            for (long long k = 0; k < N; ++k) {
                m.val[i][j] = (m.val[i][j] + lhs.val[i][k] * rhs.val[k][j] % MOD) % MOD;
            }
        }
    }
    return m;
}

template <long long N>
Matrix<N> power(Matrix<N> base, unsigned long long exponent)
{
    Matrix<N> m;
    m.normalize();
    while (exponent) {
        if (exponent & 1)
            m = m * base;
        base = base * base;
        exponent >>= 1;
    }
    return m;
}

long long power(long long base, long long exponent)
{
    long long m = 1;
    while (exponent) {
        if (exponent & 1)
            m = m * base % MOD;
        base = base * base % MOD;
        exponent >>= 1;
    }
    return m;
}

template <long long N>
ostream &operator<< (ostream &os, const Matrix<N> &m)
{
    for (long long i = 0; i < N; ++i) {
        for (long long j = 0; j < N; ++j) {
            os << m.val[i][j] << '\t';
        }
        os << '\n';
    }
    return os;
}

int main(void)
{
    long long k1, k2;
    cin >> k1 >> k2;
    long long x, y, ax, ay;
    cin >> x >> y >> ax >> ay;
    long long z;
    cin >> z;

    Matrix<2> K;
    K.val[0][0] = k1;
    K.val[0][1] = 1;
    K.val[1][0] = k2;
    K.val[1][1] = 0;

    Matrix<2> Kx = power(K, x-2);
    Matrix<2> Ky = power(K, y-2);
    Matrix<2> Kz = power(K, z-2);
    // cout << Kx << Ky << Kz;

    long long dividend = (ax * Ky.val[0][0]%MOD - ay * Kx.val[0][0]%MOD + MOD) % MOD;
    long long divisor = (Kx.val[1][0] * Ky.val[0][0]%MOD - Ky.val[1][0] * Kx.val[0][0]%MOD + MOD) % MOD;
    long long a1 = dividend * power(divisor, MOD-2) % MOD;
    long long a2 = (ax - a1 * Kx.val[1][0]%MOD + MOD) % MOD * power(Kx.val[0][0], MOD-2) % MOD;
    // cout << a1 << " " << a2 << endl;

    long long az = (a2 * Kz.val[0][0]%MOD + a1 * Kz.val[1][0]%MOD) % MOD;
    cout << az << endl;
    return 0;
}
