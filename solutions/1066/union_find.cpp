#include <iostream>
#include <map>

using namespace std;

map<string, string> s;

string represent(string n1)
{
    if (s[n1].empty() || s[n1] == n1) {
        s[n1] = n1;
    } else {
        s[n1] = represent(s[n1]);
    }
    return s[n1];
}

void merge(string n1, string n2)
{
    s[represent(n1)] = represent(n2);
}

string find(string n1, string n2)
{
    return represent(n1) == represent(n2) ? "yes" : "no";
}

int main(void)
{
    int n;
    cin >> n;
    int op;
    string n1, n2;
    for (int i = 0; i < n; ++i) {
        cin >> op >> n1 >> n2;
        if (op)
            cout << find(n1, n2) << endl;
        else
            merge(n1, n2);
    }
    return 0;
}
