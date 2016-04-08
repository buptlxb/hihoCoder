#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

bool sandbox[102][102][102];
int visited[102][102][102];
int dir[6][3] = {
    {-1, 0, 0}, {0, -1, 0}, {0, 0, -1},
    {1, 0, 0}, {0, 1, 0}, {0, 0, 1}
};

struct Cord{
    int x, y, z;
    Cord(int a, int b, int c) : x(a), y(b), z(c) {}
    Cord() : x(0), y(0), z(0) {}
} cords[100001];

int min_x, min_y, min_z, max_x, max_y, max_z;

bool bfs(int a, int b, int c, int n)
{
    sandbox[c][a][b] = false;
    bool ret = false;
    queue<Cord> q;
    q.push(Cord(a, b, c));
    visited[c][a][b] = n;
    while (!q.empty()) {
        int x = q.front().x;
        int y = q.front().y;
        int z = q.front().z;
        q.pop();
        if (x < min_x || y < min_y || z < min_z || x > max_x || y > max_y || z > max_z) {
            ret = true;
            break;
        }
        for (int i = 0; i < 6; ++i) {
            int nz = z + dir[i][0];
            int nx = x + dir[i][1];
            int ny = y + dir[i][2];
            if (!sandbox[nz][nx][ny] && n != visited[nz][nx][ny]) {
                if (visited[nz][nx][ny]) {
                    ret = true;
                    break;
                } else {
                    visited[nz][nx][ny] = n;
                    q.push(Cord(nx, ny, nz));
                }
            }
        }
    }
    return ret;
}

bool solve(int n)
{
    memset(visited, 0, sizeof(visited));
    while (n-- > 0) {
        if (!bfs(cords[n].x, cords[n].y, cords[n].z, n+1))
            return false;
    }
    return true;
}

bool build(int x, int y, int z)
{
    if (sandbox[z][x][y])
        return false;
    int i;
    for (i = 0; i < 6; ++i) {
        if (sandbox[z+dir[i][0]][x+dir[i][1]][y+dir[i][2]])
            break;
    }
    if (i == 6)
        return false;

    sandbox[z][x][y] = true;
    min_x = min(min_x, x);
    max_x = max(max_x, x);
    min_y = min(min_y, y);
    max_y = max(max_y, y);
    min_z = min(min_z, z);
    max_z = max(max_z, z);
    return true;
}

int main(void)
{
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        memset(sandbox, false, sizeof(sandbox));
        memset(sandbox[0], true, sizeof(sandbox[0]));
        int n;
        cin >> n;
        bool res = true;
        for (int j = 0; j < n; ++j) {
            int x, y, z;
            cin >> x >> y >> z;
            cords[j].x = x;
            cords[j].y = y;
            cords[j].z = z;
            if (!res)
                continue;
            res = build(x, y, z);
        }
        res = res ? solve(n) : false;
        cout << (res ? "Yes" : "No") << endl;
    }
}
