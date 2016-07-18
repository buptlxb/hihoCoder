#include <iostream>

using namespace std;

int solve(int x, int y, int z)
{
    int a = min(x, min(y, z));
    int b = max(x, max(y, z));
    int c = x - a + z + y - b;
    int ret = 0;
    if (b > a + c) {
        int ac = a + c;
        ret += ac / 10;
        b -= ret * 10;
        ac %= 10;
        if (b + ac <= 15)
            ++ret;
        else
            ret += 1 + (b - (15 - ac) + 14) / 15;
    } else
        ret = (a + b + c + 19) / 20;
    return ret;
}

int main(void)
{
    int x, y, z;
    cin >> x >> y >> z;
    cout << 6 * solve(x, y, z) << endl;
    return 0;
}
