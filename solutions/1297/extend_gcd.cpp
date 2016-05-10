#include <iostream>
#include <utility>

using namespace std;

int gcd(int a, int b)
{
    if (a % b == 0)
        return b;
    return gcd(b, a%b);
}

pair<long long, long long> extend_gcd(int a, int b)
{
    if (a % b == 0)
        return make_pair(0, 1);
    auto p = extend_gcd(b, a%b);
    return make_pair(p.second, p.first - a / b * p.second);
}

long long solve(int s1, int s2, int v1, int v2, int m)
{
    int a = v1 - v2;
    int b = m;
    int c = s2 - s1;
    if (a < 0)
        a += m;
    int d = gcd(a, b);
    if (c % d)
        return -1;
    a /= d;
    b /= d;
    c /= d;
    auto p = extend_gcd(a, b);
    long long x = (p.first * c) % b;
    while (x < 0)
        x += b;
    return x;
}

int main(void)
{
    int s1, s2, v1, v2, m;
    cin >> s1 >> s2 >> v1 >> v2 >> m;
    cout << solve(s1, s2, v1, v2, m) << endl;
}
