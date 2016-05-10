#include <iostream>
#include <vector>
#include <set>

using namespace std;

typedef vector<int>::size_type sz_t;
typedef vector<vector<int> > matrix_t;

bool match(const matrix_t &matrix, sz_t row, sz_t col)
{
    int sum = 0;
    for (sz_t i = 0; i != matrix[row].size(); ++i) {
        if (!matrix[row][i]) {
            sum = 0;
            break;
        }
        sum += matrix[row][i];
    }
    if (sum != 0 && sum != 15)
        return false;
    sum = 0;
    for (sz_t i = 0; i != matrix.size(); ++i) {
        if (!matrix[i][col]) {
            sum = 0;
            break;
        }
        sum += matrix[i][col];
    }
    if (sum != 0 && sum != 15)
        return false;
    sum = 0;
    for (sz_t i = 0; i != matrix.size(); ++i) {
        if (!matrix[i][i]) {
            sum = 0;
            break;
        }
        sum += matrix[i][i];
    }
    if (sum != 0 && sum != 15)
        return false;
    sum = 0;
    for (sz_t i = 0; i != matrix.size(); ++i) {
        if (!matrix[matrix.size()-1-i][i]) {
            sum = 0;
            break;
        }
        sum += matrix[matrix.size()-1-i][i];
    }
    if (sum != 0 && sum != 15)
        return false;
    return true;
}

void solve(matrix_t &matrix, sz_t row, sz_t col, set<int> &candidates, set<matrix_t> &ret)
{
    if (candidates.empty()) {
        ret.insert(matrix);
        return;
    }
    for (sz_t i = col; i < matrix[row].size(); ++i) {
        if (!matrix[row][i]) {
            for (auto x : candidates) {
                matrix[row][i] = x;
                if (match(matrix, row, i)) {
                    set<int> next(candidates);
                    next.erase(x);
                    solve(matrix, row+(i+1)/matrix[row].size(), (i+1)%matrix[row].size(), next, ret);
                }
            }
            matrix[row][i] = 0;
            return;
        }
    }
    for (sz_t i = row+1; i < matrix.size(); ++i) {
        for (sz_t j = 0; j < matrix[i].size(); ++j) {
            if (!matrix[i][j]) {
                for (auto x : candidates) {
                    matrix[i][j] = x;
                    if (match(matrix, i, j)) {
                        set<int> next(candidates);
                        next.erase(x);
                        solve(matrix, i+(j+1)/matrix[i].size(), (j+1)%matrix[i].size(), next, ret);
                    }
                }
                matrix[i][j] = 0;
                return;
            }
        }
    }
}

void solve(matrix_t &matrix, set<int> &candidates, set<matrix_t> &s)
{
    solve(matrix, 0, 0, candidates, s);
}

int main(void)
{
    vector<vector<int> > matrix(3, vector<int>(3));
    set<int> candidates{1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (sz_t i = 0; i != 3; ++i) {
        for (sz_t j = 0; j != 3; ++j) {
            cin >> matrix[i][j];
            candidates.erase(matrix[i][j]);
        }
    }
    set<matrix_t> s;
    solve(matrix, candidates, s);
    if (s.size() != 1) {
        cout << "Too Many" << endl;
    } else {
        matrix = *s.begin();
        for (sz_t i = 0; i != matrix.size(); ++i) {
            for (sz_t j = 0; j != matrix[i].size(); ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
