#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

void ncopy(const vector<int> &nums, int k, int m, long long &x, int &y)
{
    for (int i = 0; i < k; ++i) {
        for (auto num : nums) {
            if (y == m)
                y = 0, ++x;
            ++y;
            if (y + num > m)
                y = 0, ++x;
            y += num;
        }
    }
}

int main(void)
{
    int n, m;
    cin >> n >> m;
    vector<int> nums;
    string s;
    while(cin >> s)
        nums.push_back(s.size());

    unordered_map<int, pair<int, long long>> dict;
    long long x = 1;
    int y = -1;
    ncopy(nums, 1, m, x, y);
    dict.emplace(y, make_pair(1, x));

    for (int i = 2; i <= n; ++i) {
        ncopy(nums, 1, m, x, y);
        if (dict.find(y) != dict.end()) {
            long long remain = (n - i) % (i - dict[y].first);
            x += (n - i) / (i - dict[y].first) * (x - dict[y].second);
            ncopy(nums, remain, m, x, y);
            break;
        }
        dict.emplace(y, make_pair(1, x));
    }

    cout << x << ' ' << y << endl;
    return 0;
}
