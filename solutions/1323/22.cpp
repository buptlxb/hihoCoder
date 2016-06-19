#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <vector>

using namespace std;

bool solve(string &ret, string::size_type size, vector<int> &dict, unordered_set<string> &mem)
{
    if (ret.size() == size)
        return true;
    if (mem.find(ret) != mem.end())
        return false;
    for (int i = 0; i < dict.size(); ++i) {
        if (dict[i] == 0 || ret.size() && ret.back() == 'a'+i)
            continue;
        ret.push_back('a'+i);
        --dict[i];
        if (solve(ret, size, dict, mem))
            return true;
        ++dict[i];
        ret.pop_back();
    }
    mem.insert(ret);
    return false;
}

string solve(string &s)
{
    sort(s.begin(), s.end());
    string t(s);
    if (unique(t.begin(), t.end()) == t.end())
        return s;
    string ret;
    vector<int> dict(26);
    for (auto c : s)
        ++dict[c-'a'];
    unordered_set<string> mem;
    return solve(ret, s.size(), dict, mem) ? ret : "INVALID";
}

int main(void)
{
    string s;
    while (cin >> s)
        cout << solve(s) << endl;
    return 0;
}
