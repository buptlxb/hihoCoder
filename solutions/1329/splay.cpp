#include <iostream>
#include <set>

using namespace std;

int main(void)
{
    int n;
    cin >> n;
    set<int> s;
    while (n--) {
        int a, b;
        char c;
        cin >> c;
        if (c == 'I') {
            cin >> a;
            s.insert(a);
        } else if (c == 'Q') {
            cin >> a;
            cout << *--s.upper_bound(a) << endl;
        } else {
            cin >> a >> b;
            s.erase(s.lower_bound(a), s.upper_bound(b));
        }
    }
    return 0;
}
