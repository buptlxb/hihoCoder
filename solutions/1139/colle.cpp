#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

#define N 10000
#define M 100000

struct Edge {
    int v, w, next;
} edges[M*2];

int headers[N];
int length[N];
int n, m, k, t;

void add(int idx, int u, int v, int w)
{
    edges[idx].v = v;
    edges[idx].w = w;
    edges[idx].next = headers[u];
    headers[u] = idx;
}

bool reachable(int w)
{
    memset(length, 0, sizeof(length));
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == t)
            return true;
        if (length[u] >= k)
            continue;
        for (int i = headers[u]; i != -1; i = edges[i].next) {
            int v = edges[i].v;
            if (edges[i].w > w)
                continue;
            if (length[v] == 0) {
                length[v] = length[u] + 1;
                q.push(v);
            }
        }
    }
    return false;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> k >> t;
    memset(headers, -1, sizeof(headers));
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        add(2*i, u, v, w);
        add(2*i+1, v, u, w);
    }

    int left = 1, right = 1000000;
    while (left < right) {
        int mid = left + (right-left) / 2;
        if (reachable(mid))
            right = mid;
        else
            left = mid+1;
    }
    cout << left << endl;
    return 0;
}
