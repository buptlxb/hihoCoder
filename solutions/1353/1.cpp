#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
    int n, x, sum = 0;
    cin >> n >> x;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
        sum += nums[i];
    }
    if (sum < x) {
        cout << -1 << endl;
        return 0;
    }

    int ret = sum;
    for (int i = 1, iend = 1 << n; i < iend; ++i) {
        if (ret == x)
            break;
        int cur = 0;
        for (int j = 0; j < n; ++j) {
            if (((1 << j) & i))
                cur += nums[j];
            if (cur >= x) {
                break;
            }
        }
        if (cur >= x && cur < ret)
            ret = cur;
    }
    cout << ret << endl;
    return 0;
}
