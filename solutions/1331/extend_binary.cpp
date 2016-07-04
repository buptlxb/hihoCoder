#include <iostream>
#include <vector>

using namespace std;

unsigned long long dfs(vector<int> &num, int idx, int carry)
{
    if (idx < 0)
        return carry == 0;
    int ret = 0;
    int cur = num[idx] + carry;
    if (cur > 3)
        return 0;
    if (cur) {
        ret += dfs(num, idx-1, 2);
    }
    if (cur < 3)
        ret += dfs(num, idx-1, 0);
    return ret;
}

unsigned long long solve(int n)
{
    vector<int> num(32);
    for (int i = 0; i < 32; ++i) {
        num[i] = ((1 << i) & n) != 0;
    }
    return dfs(num, 31, 0);
}

int main(void)
{
    int n;
    cin >> n;
    cout << solve(n) << endl;
    return 0;
}
