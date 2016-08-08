#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

bool solve(vector<int> &s)
{
    map<int, int> dict;
    for (auto c : s)
        ++dict[c];
    set<pair<int, int>> heap;
    for (auto d : dict)
        heap.insert(make_pair(d.second, d.first));
    vector<int>::size_type size = s.size(), idx = 0;
    int last = -1;
    while (size) {
        auto iter = dict.find(heap.rbegin()->second);
        if (size/2 < iter->second) {
            if (last == iter->first)
                return false;
        } else {
            iter = dict.begin();
            if (iter->first == last)
                ++iter;
            assert(iter != dict.end());
        }
        heap.erase(make_pair(iter->second, iter->first));
        s[idx++] = iter->first;
        iter->second -= 1;
        if (iter->second == 0)
            dict.erase(iter);
        else
            heap.insert(make_pair(iter->second, iter->first));
        last = s[idx-1];
        --size;
    }
    return true;
}

int main(void)
{
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i)
        cin >> nums[i];
    if (!solve(nums))
        cout << -1 << endl;
    else {
        cout << nums[0];
        for (int i = 1; i < n; ++i)
            cout << ' ' << nums[i];
        cout << endl;
    }
    return 0;
}
