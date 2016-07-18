#include <iostream>
#include <vector>

using namespace std;

int solve(vector<int> &nums)
{
    if (nums.size() == 1)
        return nums[0];
    if (nums.size() == 2)
        return max(nums[0], nums[1]);
    vector<vector<int>> dp(nums.size(), vector<int>(nums.size()));
    for (int i = 0; i < nums.size(); ++i) {
        dp[i][i] = nums[i];
        if (i+1 < nums.size())
            dp[i][i+1] = max(nums[i], nums[i+1]);
    }
    for (int i = 2; i <= nums.size(); ++i) {
        for (int j = 0; j+i < nums.size(); ++j) {
            dp[j][j+i] = max(min(dp[j+2][j+i], dp[j+1][j+i-1]) + nums[j], min(dp[j][j+i-2], dp[j+1][j+i-1]) + nums[j+i]);
        }
    }
    return dp[0][nums.size()-1];
}

int main(void)
{
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    cout << solve(nums) << endl;
    return 0;
}
