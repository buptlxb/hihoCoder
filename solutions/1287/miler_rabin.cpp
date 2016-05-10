#include <iostream>
#include <cstdint>

using namespace std;

int base[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

inline uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t n)
{
    uint64_t ret = 0;
    while (b) {
        if (b & 1)
            ret = (ret + a) % n;
        a = (a << 1) % n;
        b >>= 1;
    }
    return ret;
}

inline uint64_t power_mod(uint64_t a, uint64_t u, uint64_t n)
{
    uint64_t ret = 1;
    while (u) {
        if (u & 1)
            ret = mul_mod(ret, a, n);
        a = mul_mod(a, a, n);
        u >>= 1;
    }
    return ret;
}

bool miler_rabin(uint64_t n)
{
    if (n == 2)
        return true;
    if (n < 2 || n % 2 == 0)
        return false;
    uint64_t u = n - 1;
    uint64_t times = 0;
    while ((u & 1) == 0) {
        u >>= 1;
        ++times;
    }
    for (int i = 0; i < sizeof(base)/sizeof(base[0]); ++i) {
        int a = base[i];
        if (a >= n)
            break;
        uint64_t x = power_mod(a, u, n);
        for (int i = 0; i < times; ++i) {
            uint64_t y = power_mod(x, 2, n);
            if (y == 1 && x != 1 && x != n-1)
                return false;
            x = y;
        }
        if (x != 1)
            return false;
    }
    return true;
}

int main(void)
{
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        uint64_t n;
        cin >> n;
         if (miler_rabin(n))
             cout << "Yes" << endl;
         else
             cout << "No" << endl;
    }
    return 0;
}
