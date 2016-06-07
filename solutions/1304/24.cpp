#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

struct reverse_minus {
    double operator() (double lhs, double rhs) {
        return rhs - lhs;
    }
};

struct reverse_divides {
    double operator() (double lhs, double rhs) {
        return rhs / lhs;
    }
};


bool solve(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    function<double(double, double)> ops[6] = {plus<double>(), minus<double>(), multiplies<double>(), divides<double>(), reverse_minus(), reverse_divides()};
    do {
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                for (int k = 0; k < 6; ++k) {
                    if (fabs(ops[k](ops[j](ops[i](nums[0], nums[1]), nums[2]), nums[3]) - 24) < numeric_limits<double>::epsilon())
                        return true;
                    if (fabs(ops[j](ops[i](nums[0], nums[1]), ops[k](nums[2], nums[3])) - 24) < numeric_limits<double>::epsilon())
                        return true;
                }
            }
        }
    } while (next_permutation(nums.begin(), nums.end()));
    return false;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    vector<int> nums(4);
    while (t--) {
        for (vector<int>::size_type i = 0, iend = nums.size(); i < iend; ++i)
            cin >> nums[i];
        cout << (solve(nums) ? "Yes" : "No") << '\n';
    }
    cout << flush;
    return 0;
}
