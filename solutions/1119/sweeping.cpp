#include <iostream>
#include <vector>
#include <utility>
#include <set>

using namespace std;

pair<int, int> solve(const vector<vector<int>> &board)
{
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    pair<int, int> ret(0, 0);
    vector<vector<vector<bool>>> nb(2, vector<vector<bool>>(board.size(), vector<bool>(board[0].size())));
    for (int x = 0, xend = board.size(); x < xend; ++x) {
        for (int y = 0, yend = board[x].size(); y < yend; ++y) {
            if (board[x][y] == -1)
                continue;
            if (board[x][y] == 0) { // rule 1
                for (int i = 0; i < 8; ++i) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    if (nx < 0 || ny < 0 || nx >= xend || ny >= yend || board[nx][ny] != -1)
                        continue;
                    nb[0][nx][ny] = true;
                }
            }
            int num = 0;
            for (int i = 0; i < 8; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx < 0 || ny < 0 || nx >= xend || ny >= yend || board[nx][ny] != -1)
                    continue;
                ++num;
            }
            if (num == board[x][y]) { // rule 2
                for (int i = 0; i < 8; ++i) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    if (nx < 0 || ny < 0 || nx >= xend || ny >= yend || board[nx][ny] != -1)
                        continue;
                    nb[1][nx][ny] = true;
                }
            }
            // rule 3
            for (int i = -2; i <= 2; ++i) {
                for (int j = -2; j <= 2; ++j) {
                    int nx = x + i;
                    int ny = y + j;
                    if (nx < 0 || ny < 0 || nx >= xend || ny >= yend || board[nx][ny] == -1)
                        continue;
                    int u1 = num, u2 = 0;
                    bool flag = true;
                    for (int i = 0; i < 8; ++i) {
                        int nx2 = nx + dx[i];
                        int ny2 = ny + dy[i];
                        if (nx2 < 0 || ny2 < 0 || nx2 >= xend || ny2 >= yend || board[nx2][ny2] != -1)
                            continue;
                        flag &= abs(nx2-x) <= 1 && abs(ny2-y) <= 1;
                        ++u2;
                    }
                    if (flag && u1 > u2 && u1-u2 == board[x][y] - board[nx][ny]) {
                        for (int i = 0; i < 8; ++i) {
                            int nx2 = x + dx[i];
                            int ny2 = y + dy[i];
                            if (nx2 < 0 || ny2 < 0 || nx2 >= xend || ny2 >= yend || board[nx2][ny2] != -1 || (abs(nx2-nx) <= 1 && abs(ny2-ny) <= 1))
                                continue;
                            nb[1][nx2][ny2] = true;
                        }

                    }
                }
            }
        }
    }
    for (int x = 0, xend = board.size(); x < xend; ++x) {
        for (int y = 0, yend = board[x].size(); y < yend; ++y) {
            if (board[x][y] != -1)
                continue;
            ret.first += nb[1][x][y];
            ret.second += nb[0][x][y];
        }
    }
    return ret;
}

int main(void)
{
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> board(n, vector<int>(m));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                cin >> board[i][j];
        pair<int, int> p = solve(board);
        cout << p.first << " " << p.second << endl;
    }
    return 0;
}
