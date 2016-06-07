#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    int virus;
    int degree;
    vector<int> next;
    Node() : virus(0), degree(0) {}
};

const int MOD = 142857;

int solve(vector<Node> &network) {
    queue<int> q;
    for (int i = 0, iend = network.size(); i < iend; ++i)
        if (network[i].degree == 0)
            q.push(i);
    int ret = 0;
    while (!q.empty()) {
        int idx = q.front();
        q.pop();
        ret = (ret + network[idx].virus) % MOD;
        for (auto v : network[idx].next) {
            network[v].virus = (network[v].virus + network[idx].virus) % MOD;
            if (--network[v].degree == 0)
                q.push(v);
        }
    }
    return ret;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, k;
    cin >> n >> m >> k;
    vector<Node> network(n);
    while (k--) {
        int a;
        cin >> a;
        network[--a].virus = 1;
    }
    while (m--) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        network[u].next.push_back(v);
        network[v].degree += 1;
    }
    cout << solve(network) << endl;
    return 0;
}
