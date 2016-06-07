#include <iostream>
#include <vector>
#include <map>

using namespace std;

char photo[50][50];
bool visited[50][50];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int m, n;

int dfs(int x, int y, string &s)
{
    visited[x][y] = true;
    int ret = 1;
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || ny < 0 || nx >= 50 || ny >= 50 || visited[nx][ny] || photo[nx][ny] != '#')
            continue;
        s.push_back(i+'0');
        ret += dfs(nx, ny, s);
        s.push_back('$');
    }
    return ret;
}

void solve(int &a, int &b, int &c) {
    a = 0;
    map<int, int> area;
    map<string, int> shape;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!visited[i][j] && photo[i][j] == '#') {
                string s;
                ++area[dfs(i, j, s)];
                ++a;
                ++shape[s];
            }
        }
    }
    b = area.size();
    c = shape.size();
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> photo[i][j];
    int a, b, c;
    solve(a, b, c);
    cout << a << " " << b << " " << c << endl;
    return 0;
}
