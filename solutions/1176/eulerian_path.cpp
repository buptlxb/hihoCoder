#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
    int n, m;
    cin >> n >> m;
    vector<int> degree(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        ++degree[--u];
        ++degree[--v];
    }
    int cnt = 0;
    while (--n >= 0) {
        if (!degree[n]) {
            cnt = 1;
            break;
        }
        if (degree[n] % 2)
            ++cnt;
    }
    cout << (cnt == 2 || cnt == 0 ? "Full" : "Part") << endl;
    return 0;
}
