#include <iostream>
#include <vector>
#include <utility>

using namespace std;

#define N 1000
bool region[N][N];
pair<int, int> board[N][N];

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
int islands;

pair<int, int> sfind(int x, int y)
{
    if (board[x][y].first == x && board[x][y].second == y)
        return make_pair(x, y);
    return board[x][y] = sfind(board[x][y].first, board[x][y].second);
}

bool sunion(int x1, int y1, int x2, int y2)
{
    auto p1 = sfind(x1, y1), p2 = sfind(x2, y2);
    if (p1 == p2)
        return false;
    board[p1.first][p1.second] = p2;
    return true;
}

void build(int x, int y)
{
    ++islands;
    region[x][y] = true;
    board[x][y] = make_pair(x, y);
    for (int i = 0; i < sizeof(dx)/sizeof(dx[0]); ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || ny < 0 || nx >= N || ny >= N || !region[nx][ny])
            continue;
        if (sunion(nx, ny, x, y))
            --islands;
    }
}

int main(void)
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        build(x, y);
        cout << islands << '\n';
    }
    cout << flush;
    return 0;
}
