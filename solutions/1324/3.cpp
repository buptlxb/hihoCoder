#include <iostream>
#include <vector>
#include <set>
#include <cctype>
#include <queue>

using namespace std;

int n, m, a, b, c, d;

char maze[100][100];
int visited[100][100];

struct Status {
    int x, y, step;
    set<char> keys;
    Status (int a, int b, int s, set<char> &k) : x(a), y(b), step(s), keys(k) {}
};

ostream & operator<< (ostream &os, const Status &s) {
    os << s.x << ", " << s.y << ": " << s.step;
    for (auto k : s.keys)
        os << " " << k;
    return os;
}

void print() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << visited[i][j];
        }
        cout << endl;
    }
}

int solve()
{
    queue<Status> q;
    set<char> s;
    Status start(a, b, 0, s);
    if (islower(maze[a][b]))
        start.keys.insert(maze[a][b]);
    q.push(start);
    visited[a][b] = start.keys.size()+1;
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    while (!q.empty()) {
        Status cur = q.front();
        q.pop();
        //cout << cur << endl;
        //print();
        if (cur.x == c && cur.y == d)
            return cur.step;
        for (int i = 0; i < 4; ++i) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (nx < 0 || ny < 0 || nx >= n || ny >= m || maze[nx][ny] == '#' || visited[nx][ny] >= cur.keys.size()+1 ||
                    isupper(maze[nx][ny]) && cur.keys.find(tolower(maze[nx][ny])) == cur.keys.end())
                continue;
            Status next(nx, ny, cur.step+1, cur.keys);
            if (islower(maze[nx][ny]))
                next.keys.insert(maze[nx][ny]);
            q.push(next);
            visited[nx][ny] = cur.keys.size()+1;
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
