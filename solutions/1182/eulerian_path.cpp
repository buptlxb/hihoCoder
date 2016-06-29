#include <iostream>
#include <stack>

using namespace std;

bool graph[1<<15][1<<15];

void fleury(int u, int mask, stack<int> &s)
{
    int v = (u & mask) << 1;
    for (int i = 0; i < 2; ++i) {
        if (graph[u][v+i]) {
            graph[u][v+i] = false;
            fleury(v+i, mask, s);
        }
    }
    s.push(u);
}

string solve(int n)
{
    int size = 1 << (n-1);
    int mask = (1 << (n-2)) - 1;
    for (int i = 0; i < size; ++i) {
        int j = i & mask;
        graph[i][(j << 1)] = graph[i][(j << 1)|1] = true;
    }
    stack<int> s;
    fleury(0, mask, s);
    string ret;
    s.pop();
    while (!s.empty()) {
        ret.push_back(s.top() % 2 + '0');
        s.pop();
    }
    return ret;
}

int main(void)
{
    int n;
    cin >> n;
    cout << solve(n) << endl;
    return 0;
}
