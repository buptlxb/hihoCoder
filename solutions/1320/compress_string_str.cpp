#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

string compress(const string s, unordered_map<string, string> &mem)
{
    if (s.size() < 5)
        return s;
    if (mem.find(s) != mem.end())
        return mem[s];
    for (string::size_type i = 1, iend = s.size()/2; i <= iend; ++i) {
        string::size_type j = 0, jend = s.size()-1;
        string dup = s.substr(0, i);
        while (j <= jend && s.substr(j, i) == dup)
            j += i;
        if (j >= s.size())
            return mem[s] = to_string(s.size()/i) + "(" + compress(dup, mem) + ")";
    }
    string c = s;
    for (string::size_type i = 1, iend = s.size(); i < iend; ++i) {
        string left = s.substr(0, i), right = s.substr(i);
        string t = compress(s.substr(0, i), mem) + compress(s.substr(i), mem);
        if (t.size() < c.size())
            c = t;
    }
    return mem[s] = c;
}

int main(void)
{
    int t;
    cin >> t;
    string s;
    while (t--) {
        unordered_map<string, string> mem;
        cin >> s;
        cout << compress(s, mem).size() << endl;
    }
    return 0;
}
