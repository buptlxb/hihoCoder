#include <iostream>
#include <cstring>
#include <set>
#include <queue>
#include <utility>

#define N 501
#define M 501
#define UDF 0x3f3f3f3f

using namespace std;

int A[M];
int B[N];
int n, m;
set<pair<int, int>> dead;

struct Status{
    int x, y, d;
    Status(int a, int b, int c) : x(a), y(b), d(c) {}
};

int visit[N][M];

int solve(int x, int y, int p, int q)
{
    static int dx[] = {-1, 0, 1, 0};
    static int dy[] = {0, 1, 0, -1};

    queue<Status> sq;
    sq.push(Status(x, y, 0));
    visit[x][y] = 0;
    while (!sq.empty()) {
        int cx = sq.front().x;
        int cy = sq.front().y;
        int cd = sq.front().d;
        sq.pop();
        for (int i = 0; i < 4; ++i) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if (nx <= 0 || ny <= 0 || nx > n || ny > m || dead.find(make_pair(nx, ny)) != dead.end())
                continue;
            int nd = dx[i] == 0 ? cd + A[min(cy, ny)] : cd + B[min(cx, nx)];
            if (visit[nx][ny] <= nd)
                continue;
            if (nx != p || ny != q)
                sq.push(Status(nx, ny, nd));
            visit[nx][ny] = nd;
        }
    }
    return visit[p][q] == UDF ? -1 : visit[p][q];
}

int main(void)
{
    cin >> n >> m;
    for (int i = 1; i < n; ++i)
        cin >> B[i];
    for (int i = 1; i < m; ++i)
        cin >> A[i];
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int x, y;
        cin >> x >> y;
        dead.insert(make_pair(x, y));
    }
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        int x, y, p, q;
        cin >> x >> y >> p >> q;
        memset(visit, UDF, sizeof(visit));
        cout << solve(x, y, p, q) << endl;
    }
    return 0;
}
