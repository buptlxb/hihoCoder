#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

#define N 1000
struct Cycle {
    int x, y, r, tag;
} radar[N];

int w, h, n;

inline long long square(long long x)
{
    return x * x;
}

inline long long dist(int i, int j)
{
    return (square(radar[i].x-radar[j].x) + square(radar[i].y-radar[j].y));
}

bool dfs(int idx)
{
    for (int i = 0; i < n; ++i) {
        if (radar[i].tag == 1)
            continue;
        if (dist(idx, i) > square(radar[idx].r+radar[i].r))
            continue;
        if (radar[i].tag == 2)
            return false;
        radar[i].tag = 1;
        if (!dfs(i))
            return false;
    }
    return true;
}

string solve()
{
    vector<int> ones;
    for (int i = 0; i < n; ++i) {
        if (radar[i].y - radar[i].r <= 0 && radar[i].y + radar[i].r >= h)
            return "NO";
        if (radar[i].y - radar[i].r <= 0) {
            radar[i].tag = 1;
            ones.push_back(i);
        } else if (radar[i].y + radar[i].r >= h)
            radar[i].tag = 2;
        else {
            radar[i].tag = 0;
        }
    }
    for (auto c : ones) {
        if (!dfs(c))
            return "NO";
    }
    return "YES";
}

int main(void)
{
    int t;
    cin >> t;
    while (t--) {
        cin >> w >> h >> n;
        for (int i = 0; i < n; ++i) {
            cin >> radar[i].x >> radar[i].y >> radar[i].r;
        }
        cout << solve() << endl;
    }
    return 0;
}
