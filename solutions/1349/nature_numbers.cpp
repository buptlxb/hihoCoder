#include <iostream>

using namespace std;

int main(void)
{
    unsigned long long n;
    cin >> n;
    unsigned long long digit = 1, cnt = 1, base = 1;
    while (n > cnt + digit*9*base) {
        cnt += digit * 9 * base;
        ++digit;
        base *= 10;
    }
    n -= cnt;
    unsigned long long idx = n / digit + base;
    cout << to_string(idx)[n % digit] << endl;
    return 0;
}
