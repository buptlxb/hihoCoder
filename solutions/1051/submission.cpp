#include <iostream>
#include <vector>

using namespace std;

int solve(const vector<int> &nums, int m)
{
    int res = 0;
    m += 1;
    for (vector<int>::size_type i = m, iend = nums.size(); i < iend; ++i) {
        res = max(res, nums[i] - nums[i-m]);
    }
    return res - 1;
}

int main(void)
{
    int t; cin >> t;
    for (int i = 0; i < t; ++i) {
        int n, m; cin >> n >> m;
        vector<int> nums(n+2);
        for (int j = 1; j <= n; ++j) {
            cin >> nums[j];
        }
        nums.back() = 101;
        if (m >= n || n == 0)
            cout << 100 << endl;
        else
            cout << solve(nums, m) << endl;
    }
    return 0;
}
