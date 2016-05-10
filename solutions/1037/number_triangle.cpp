#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solve(const vector<vector<int>> &triangle)
{
    vector<int> dp(triangle.size()+1);
    for (vector<int>::size_type i = 1, iend = triangle.size(); i < iend; ++i) {
        for (vector<int>::size_type j = triangle[i].size()-1; j > 1; --j)
        {
            dp[j-1] = max(dp[j-1], dp[j-2]) + triangle[i][j-1];
        }
    }
    return *max_element(dp.begin(), dp.end());
}

int main(void)
{
    int n;
    while (cin >> n) {
        vector<vector<int>> triangle(n+1);
        for (int i = 0; i <= n; ++i) {
            triangle[i].resize(i+2);
            for (int j = 1; j <= i; ++j)
                cin >> triangle[i][j];
        }
        cout << solve(triangle) << endl;
    }
    return 0;
}
