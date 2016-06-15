#include <iostream>

using namespace std;

int matrix[100][100];
bool visited[100][100];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
int n, m;

int dfs(int x, int y)
{
    int ret = 1;
    visited[x][y] = true;
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= n || ny >= m || nx < 0 || ny < 0)
            continue;
        if (!visited[nx][ny] && matrix[nx][ny] == matrix[x][y])
            ret += dfs(nx, ny);
    }
    return ret;
}

int cal(int x, int y)
{
    int r = 0;
    visited[x][y] = false;
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= n || ny >= m || nx < 0 || ny < 0)
            continue;
        if (visited[nx][ny])
            ++r;
    }
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= n || ny >= m || nx < 0 || ny < 0)
            continue;
        if (visited[nx][ny])
            r += cal(nx, ny);
    }
    return r;
}

int solve(int x, int y)
{
    int sum = dfs(x, y);
    return sum*4 - 2*cal(x, y);
}

int main(void)
{
    int x, y;
    cin >> n >> m >> x >> y;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> matrix[i][j];
    cout << solve(x, y) << endl;
    return 0;
}
