#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

const int MOD = 12357;

template <typename T>
struct Matrix {
    typedef typename vector<T>::size_type size_type;
    vector<vector<T>> value;
    Matrix(size_type row, size_type col) : value(row, vector<T>(col)) {}
    size_type row() const { return value.size(); }
    size_type col() const { return value.front().size(); }
    void normalize() { 
        for (size_type i = 0, iend = value.size(); i < iend; ++i) {
            value[i].assign(value[i].size(), 0);
            value[i][i] = 1;
        }
    }
};

template <typename T>
ostream & operator<< (ostream &os, const Matrix<T> &m)
{
    for (typename Matrix<T>::size_type i = 0, iend = m.row(); i < iend; ++i) {
        for (typename Matrix<T>::size_type j = 0, jend = m.col(); j < jend; ++j) {
            os << m.value[i][j] << " ";
        }
        cout << "\n";
    }
    return os;
}

template<typename T>
Matrix<T> mul_mod(const Matrix<T> &lhs, const Matrix<T> &rhs, int mod)
{
    assert(!lhs.value.empty() && !rhs.value.empty());
    assert(lhs.value.front().size() == rhs.value.size());
    Matrix<T> ret(lhs.row(), lhs.col());
    for (typename Matrix<T>::size_type i = 0, iend = lhs.row(); i < iend; ++i) {
        for (typename Matrix<T>::size_type j = 0, jend = lhs.col(); j < jend; ++j) {
            for (typename Matrix<T>::size_type k = 0, kend = rhs.row(); k < kend; ++k){
                ret.value[i][j] = (ret.value[i][j] + ((unsigned long long)lhs.value[i][k]) * rhs.value[k][j]) % mod;
            }
        }
    }
    return ret;
}

template<typename T>
Matrix<T> & power_mod(Matrix<T> &m, int exp, int mod)
{
    Matrix<T> t = m;
    m.normalize();
    while (exp) {
        if (exp & 1)
            m = mul_mod(m, t, mod);
        exp >>= 1;
        t = mul_mod(t, t, mod);
    }
    return m;
}

void dfs(int x, int y, int col, int k, Matrix<int> &m)
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
    Matrix<int> m(1<<k, 1<<k);
    dfs(0, 0, 0, k, m);
    power_mod(m, n, MOD);
    return m.value.back().back();
}

int main(void)
{
    int k, n;
    cin >> k >> n;
    cout << solve(k, n) << endl;
    return 0;
}
