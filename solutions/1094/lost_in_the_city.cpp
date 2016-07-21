#include <iostream>
#include <vector>

using namespace std;

typedef vector<char>::size_type sz_t;
inline bool equal(const vector<vector<char>> &board, const vector<vector<char>> &surroundings, sz_t x, sz_t y)
{
    if (board[x][y] != surroundings[1][1])
        return false;
    bool ret = true;
    // north
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[x+i-1][y+j-1] != surroundings[i][j]) {
                ret = false;
                break;
            }
        }
    }
    if (ret)
        return ret;
    // east
    ret = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[x+i-1][y+j-1] != surroundings[j][2-i]) {
                ret = false;
                break;
            }
        }
    }
    if (ret)
        return ret;
    // south
    ret = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[x+i-1][y+j-1] != surroundings[2-i][2-j]) {
                ret = false;
                break;
            }
        }
    }
    if (ret)
        return ret;
    // west
    ret = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[x+i-1][y+j-1] != surroundings[2-j][i]) {
                ret = false;
                break;
            }
        }
    }
    return ret;
}

void solve(const vector<vector<char>> &board, const vector<vector<char>> &surroundings)
{
    for (sz_t i = 1, iend = board.size()-1; i < iend; ++i) {
        for (sz_t j = 1, jend = board[i].size()-1; j < jend; ++j) {
            if (equal(board, surroundings, i, j))
                cout << i+1 << " " << j+1 << endl;
        }
    }
}

int main(void)
{
    int n, m;
    cin >> n >> m;
    vector<vector<char>> board(n, vector<char>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> board[i][j];
        }
    }
    vector<vector<char>> surroundings(3, vector<char>(3));
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            cin >> surroundings[i][j];
    solve(board, surroundings);
    return 0;
}
