#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>

using namespace std;

unsigned long long gcd(int a, int b)
{
    if (a % b == 0)
        return b;
    return gcd(b, a % b);
}

unsigned long long lcm(int a, int b)
{
    return a / gcd(a, b) * b;
}

unsigned long long solve(const vector<int> &p)
{
    unsigned long long ret = 1;
    for (int i = 1; i < p.size(); ++i) {
        int t = 0, j = i;
        do {
            j = p[j];
            ++t;
        } while (j != i);
        ret = lcm(ret, t);
    }
    return ret;
}

int main(void)
{
    int n;
    cin >> n;
    vector<int> p(n+1);
    for (int i = 1; i <= n; ++i)
        cin >> p[i];
    cout << solve(p) << endl;
    return 0;
}
