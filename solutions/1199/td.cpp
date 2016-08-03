#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MONEY 200000000

struct Level {
    int p, q;
    int pt, qt;
    vector<int> children;
};

struct LevelCmp : less<int> {
    vector<Level> &levels;
    LevelCmp(vector<Level> &l) : levels(l) {}
    bool operator() (int lhs, int rhs) {
        return levels[lhs].qt > levels[rhs].qt;
    }
};


void dfs(vector<Level> &levels, int root)
{
    int money = MONEY;
    int min_money = MONEY;
    for (auto c : levels[root].children)
        dfs(levels, c);

    money -= levels[root].p;
    min_money = min(min_money, money);
    money += levels[root].q;

    sort(levels[root].children.begin(), levels[root].children.end(), LevelCmp(levels));

    for (auto c : levels[root].children) {
        money -= levels[c].pt;
        min_money = min(min_money, money);
        money += levels[c].qt;
    }

    levels[root].pt = MONEY - min_money;
    levels[root].qt = money - min_money;
}

int main(void)
{
    int n;
    cin >> n;
    vector<Level> levels(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> levels[i].p >> levels[i].q;
    }
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        levels[min(a, b)].children.push_back(max(a,b));
    }
    dfs(levels, 1);
    cout << levels[1].pt << endl;
    return 0;
}
