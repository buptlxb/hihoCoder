#include <iostream>
#include <algorithm>

using namespace std;

string solve(string &s)
{
    if (s.size() == 1)
        return s;
    sort(s.begin(), s.end());
    string::size_type i = 0, iend = 0, end = s.size();
    while (iend+1 < end && s[iend] == s[iend+1])
        ++iend;
    if (iend+1 == end)
        return "INVALID";
    string::size_type j = ++iend;
    string ret;
    while (i < end) {
        ret += s[i++];
        while (i < iend && j < end) {
            ret += s[j++];
            ret += s[i++];
        }
        if (j == end)
            return i == iend ? ret : "INVALID";
        i = iend = j;
        while (iend+1 < end && s[iend] == s[iend+1])
            ++iend;
        if (iend+1 == end)
            return "INVALID";
        j = ++iend;
    }
    return ret;
}

int main(void)
{
    string s;
    cin >> s;
    cout << solve(s) << endl;
    return 0;
}
