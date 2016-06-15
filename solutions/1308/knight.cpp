#include <iostream>
#include <cstring>
#include <limits>
#include <queue>

using namespace std;

int board[3][8][8];
int dx[] = {-2, -2, -1, 1, 2, 2, 1, -1};
int dy[] = {-1, 1, 2, 2, 1, -1, -2, -2};

void fill(int idx, int a, int b)
{
    queue<pair<int, int> > q;
    q.push(make_pair(a, b));
    int step = 1, prev = 1, cur = 0;
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        board[idx][x][y] = step;
        q.pop();
        for (int i = 0; i < 8; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || ny < 0 || nx >= 8 || ny >= 8 || board[idx][nx][ny])
                continue;
            q.push(make_pair(nx, ny));
            ++cur;
        }
        if (--prev == 0) {
            swap(prev, cur);
            ++step;
        }
    }
}

void print(int idx)
{
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            cout << board[idx][x][y] << '\t';
        }
        cout << '\n';
    }
    cout << endl;
}

int solve()
{
    int ret = numeric_limits<int>::max();
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            ret = min(ret, board[0][x][y]+board[1][x][y]+board[2][x][y]);
        }
    }
    return ret-3;
}

int main(void)
{
    int t;
    cin >> t;
    while (t--) {
        char c;
        int n;
        for (int i = 0; i < 3; ++i) {
            cin >> c >> n;
            fill(i, c-'A', n-1);
        }
        cout << solve() << endl;
        memset(board, 0, sizeof(board));
    }
    return 0;
}
