#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

string::size_type eliminate(string s)
{
    while (true) {
        if (s.size() == 0)
            return 0;
        int cnt = 0;
        int prev = s[0];
        string t;
        for (string::size_type i = 0, iend = s.size(); i < iend; ++i) {
            if (prev == s[i]) {
                ++cnt;
            } else {
                if (cnt == 1) {
                    t.push_back(prev);
                }
                prev = s[i];
                cnt = 1;
            }
        }
        if (cnt == 1)
            t.push_back(prev);
        if (t.size() == s.size())
            break;
        s.swap(t);
    }
    return s.size();
}

int solve(const string &s)
{
    string::size_type m = s.size();
    for (char c = 'A'; c <= 'C'; ++c) {
        for (string::size_type i = 0, iend = s.size(); i != iend; ++i) {
            string t(s);
            t.insert(i, 1, c);
            m = min(m, eliminate(t));
        }
        m = min(m, eliminate(s + c));
    }
    return s.size() - m + 1;
}

int main(void)
{
    int t;
    cin >> t;
    string s;
    for (int i = 0; i < t; ++i) {
        cin >> s;
        cout << solve(s) << endl;
    }
    return 0;
}
