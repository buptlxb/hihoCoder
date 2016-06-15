#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

string::size_type compress(const string s, unordered_map<string, string::size_type> &mem)
{
    string::size_type len = s.size();
    if (len < 5)
        return len;
    if (mem.find(s) != mem.end())
        return mem[s];
    for (string::size_type i = 1, iend = len/2; i <= iend; ++i) {
        string::size_type j = 0, jend = len-1;
        string dup = s.substr(0, i);
        while (j <= jend && s.substr(j, i) == dup)
            j += i;
        if (j >= len)
            return mem[s] = to_string(len/i).size() + compress(dup, mem) + 2;
    }
    string::size_type m = len;
    for (string::size_type i = 1, iend = len; i < iend; ++i) {
        m = min(compress(s.substr(0, i), mem) + compress(s.substr(i), mem), m);
    }
    return mem[s] = m;
}

int main(void)
{
    int t;
    cin >> t;
    string s;
    unordered_map<string, string::size_type> mem;
    while (t--) {
        cin >> s;
        cout << compress(s, mem) << endl;
    }
    return 0;
}
