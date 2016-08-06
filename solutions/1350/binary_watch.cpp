#include <iostream>
#include <iomanip>

using namespace std;

int ones(int x)
{
    int ret = 0;
    while (x) {
        ++ret;
        x &= x-1;
    }
    return ret;
}

int main(void)
{
    int x;
    cin >> x;
    for (int h = 0; h < 24; ++h) {
        for (int m = 0; m < 60; ++m) {
            if (ones(h) + ones(m) == x)
                cout << setfill('0') << setw(2) << h << ":" << setfill('0') << setw(2) << m << '\n';
        }
    }
    cout << flush;
    return 0;
}
