#include <iostream>
#include <map>
#include <set>

using namespace std;

int main(void)
{
    int n;
    cin >> n;
    map<pair<string, string>, int> dict;
    for (int i = 0; i < n; ++i) {
        int m;
        cin >> m;
        string id, date, price;
        set<pair<string, string>> cur;
        for (int j = 0; j < m; ++j) {
            cin >> id >> date >> price;
            pair<string, string> p(id, price);
            if (!cur.insert(p).second)
                continue;
            ++dict[p];
        }
    }
    for (auto i = dict.begin(), iend = dict.end(); i != iend; ++i)
        if (i->second == n)
            cout << i->first.first << '\n';
    cout << flush;
    return 0;
}
