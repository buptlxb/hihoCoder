#include <iostream>
#include <vector>

using namespace std;

unsigned long long gcd(unsigned long long a, unsigned long long b)
{
    if (a % b == 0)
        return b;
    return gcd(b, a % b);
}

unsigned long long divisors(unsigned long long x)
{
    unsigned long long i, s = 0;
    for (i = 1; i*i < x; ++i)
        if (x % i == 0)
            s += 2;
    if (i * i == x)
        ++s;
    return s;
}

int main(void)
{
    unsigned long long n, m;
    cin >> n >> m;
    unsigned long long g = gcd(n, m);
    unsigned long long s = divisors(g);
    unsigned long long ns = divisors(n);
    unsigned long long ms = divisors(m);

    ns *= ms;
    while ((ms = gcd(ns, s)) != 1) {
        ns /= ms;
        s /= ms;
    }
    cout << ns << " " << s << endl;
    return 0;
}
