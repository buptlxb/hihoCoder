#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

string solve(string &s)
{
    map<char, int> dict;
    for (auto c : s)
        ++dict[c];
    string ret;
    string::size_type size = s.size();
    char last = '\0';
    while (size) {
        auto iter = dict.begin();
        for (auto i = dict.begin(), iend = dict.end(); i != iend; ++i)
            if (iter->second < i->second)
                iter = i;
        if (size/2 < iter->second) {
            if (last != iter->first) {
                ret.push_back(iter->first);
                iter->second -= 1;
                if (iter->second == 0)
                    dict.erase(iter);
            } else
                return "INVALID";
        } else {
            auto i = dict.begin();
            if (i->first == last)
                ++i;
            assert(i != dict.end());
            ret.push_back(i->first);
            i->second -= 1;
            if (i->second == 0)
                dict.erase(i);
        }
        last = ret.back();
        --size;
    }
    return ret;
}

int main(void)
{
    string s;
    while (cin >> s)
        cout << solve(s) << endl;
    return 0;
}
