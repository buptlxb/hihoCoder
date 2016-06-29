#include <iostream>
#include <vector>
#include <map>

using namespace std;

int solve(string &s, string::size_type idx, string::size_type end, vector<int> &nums, map<string::size_type, int> &mem)
{
    while (idx < end && s[idx] == '0')
        ++idx;
    if (idx == end)
        return 0;
    if (mem.find(idx) != mem.end())
        return mem[idx];
    return mem[idx] = min(solve(s, idx+1, end, nums, mem)+1, nums[idx]);
}

int solve(string &s)
{
    vector<int> nums(s.size());
    int cnt = 0;
    for (string::size_type i = s.size(); i > 0; --i) {
        if (s[i-1] == '0')
            ++cnt;
        else
            nums[i-1] = cnt;
    }
    string::size_type end = s.size();
    while (end > 0 && s[end-1] == '1')
        --end;
    map<string::size_type, int> mem;
    return solve(s, 0, end, nums, mem);
}

int main(void)
{
    int t;
    cin >> t;
    string s;
    while (t--) {
        cin >> s;
        cout << solve(s) << endl;
    }
    return 0;
}
