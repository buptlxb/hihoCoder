#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct Point {
    int id, x, y;
};

istream & operator>> (istream &is, Point &p)
{
    is >> p.x >> p.y;
    return is;
}

struct x_less : less<Point> {
    bool operator() (const Point &lhs, const Point &rhs) {
        return lhs.x < rhs.x || lhs.x == rhs.x && lhs.y < rhs.y;
    }
};

struct y_less : less<Point> {
    bool operator() (const Point &lhs, const Point &rhs) {
        return lhs.y < rhs.y || lhs.y == rhs.y && lhs.x < rhs.x;
    }
};

typedef vector<vector<int>> Graph;

int dist(int a, int b, const vector<Point> &points)
{
    return min(abs(points[a].x - points[b].x), abs(points[a].y - points[b].y));
}

int spfa(Graph &graph, int src, int dst, const vector<Point> &points)
{
    vector<int> distances(graph.size(), 1000000001);
    vector<int> visited(graph.size());
    queue<int> q;

    visited[src] = true;
    distances[src] = 0;
    q.push(src);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        visited[u] = false;
        for (auto p : graph[u]) {
            int d = dist(p, u, points);
            if (distances[p] > distances[u] + d) {
                distances[p] = distances[u] + d;
                if (!visited[p]) {
                    visited[p] = true;
                    q.push(p);
                }
            }
        }
    }
    return distances[dst];
}

void build(vector<Point> points, Graph &graph)
{
    sort(points.begin(), points.end(), x_less());
    for (int i = 0, iend = points.size(); i < iend; ) {
        int j, jend;
        for (j = i+1, jend = iend; j < jend && points[i].x == points[j].x; ++j) {
            graph[points[i].id].push_back(points[j].id);
            graph[points[j].id].push_back(points[i].id);
        }
        if (j < jend) {
            graph[points[i].id].push_back(points[j].id);
            graph[points[j].id].push_back(points[i].id);
        }
        i = j;
    }

    sort(points.begin(), points.end(), y_less());
    for (int i = 0, iend = points.size(); i < iend; ) {
        int j, jend;
        for (j = i+1, jend = iend; j < jend && points[i].y == points[j].y; ++j) {
            graph[points[i].id].push_back(points[j].id);
            graph[points[j].id].push_back(points[i].id);
        }
        if (j < jend) {
            graph[points[i].id].push_back(points[j].id);
            graph[points[j].id].push_back(points[i].id);
        }
        i = j;
    }
}

int solve(vector<Point> &points)
{
    if (points.size() < 2)
        return 0;

    Graph graph(points.size());
    build(points, graph);

    return spfa(graph, 0, points.size()-1, points);
}

int main(void)
{
    int n;
    cin >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i];
        points[i].id = i;
    }
    cout << solve(points) << endl;
    return 0;
}
