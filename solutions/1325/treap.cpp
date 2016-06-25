#include <iostream>
#include <set>

using namespace std;

int main(void)
{
    int n;
    cin >> n;
    set<int> s;
    for (int i = 0; i < n; ++i) {
        char c;
        int k;
        cin >> c >> k;
        if (c == 'I')
            s.insert(k);
        else
            cout << *(--s.upper_bound(k)) << endl;
    }
    return 0;
}
