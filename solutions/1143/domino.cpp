#include <iostream>

using namespace std;

const int mod = 19999997;

int solve(int n)
{
    int a = 1, b = 1;
    for (int i = 1; i < n; ++i) {
        int c = (a + b) % mod;
        b = a;
        a = c;
    }
    return a;
}

int main(void)
{
    int n;
    while (cin >> n) {
        cout << solve(n) << endl;
    }
    return 0;
}
