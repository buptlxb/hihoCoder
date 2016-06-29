#include <iostream>
#include <vector>
#include <bitset>
#include <cctype>
#include <queue>

using namespace std;

int n, m, a, b, c, d;

char maze[100][100];
bool visited[64][100][100];

struct Status {
    int x, y, step;
    char keys;
    Status (int a, int b, int s, char k) : x(a), y(b), step(s), keys(k) {}
};

ostream & operator<< (ostream &os, const Status &s) {
    os << s.x << ", " << s.y << ": " << s.step;
    for (size_t i = 0, iend = sizeof(s.keys); i < iend; ++i)
        if (s.keys & (1 << i))
            os << " " << (char)('a'+i);
    return os;
}

void print(char idx) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << visited[idx][i][j] << " ";
        }
        cout << endl;
    }
}

int solve()
{
    queue<Status> q;
    Status start(a, b, 0, 1);
    if (islower(maze[a][b]))
        start.keys |= 1 << (maze[a][b] - 'a' + 1);
    q.push(start);
    visited[start.keys][a][b] = true;
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    while (!q.empty()) {
        Status cur = q.front();
        q.pop();
        cout << cur << endl;
        print(cur.keys);
        if (cur.x == c && cur.y == d)
            return cur.step;
        for (int i = 0; i < 4; ++i) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (nx < 0 || ny < 0 || nx >= n || ny >= m || maze[nx][ny] == '#' || visited[cur.keys][nx][ny] ||
                    isupper(maze[nx][ny]) && (cur.keys&(1 << (maze[nx][ny]-'A'+1))) == 0)
                continue;
            Status next(nx, ny, cur.step+1, cur.keys);
            if (islower(maze[nx][ny]))
                next.keys |= 1 << (maze[nx][ny]-'a'+1);
            q.push(next);
            visited[next.keys][nx][ny] = true;
        }
    }
    return -1;
}

int main(void)
{
    int k;
    cin >> n >> m >> k >> a >> b >> c >> d;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < m; ++j) {
            maze[i][j] = s[j];
        }
    }
    for (int i = 0; i < k; ++i) {
        int x, y;
        cin >> x >> y;
        maze[x][y] = i + 'a'; 
    }
    cout << solve() << endl;
    return 0;
}
