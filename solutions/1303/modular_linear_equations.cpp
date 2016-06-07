#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

int64_t gcd(int64_t a, int64_t b)
{
    if (a % b == 0)
        return b;
    return gcd(b, a % b);
}

pair<int64_t, int64_t> extend_gcd(int64_t a, int64_t b)
{
    if (a % b == 0)
        return {0, 1};
    auto p = extend_gcd(b, a%b);
    return {p.second, p.first - a/b*p.second};
}

int64_t solve(const vector<int> &ms, const vector<int> &rs) {
    int64_t m = ms[0], r = rs[0];
    for (vector<int>::size_type i = 1, iend = ms.size(); i < iend; ++i) {
        int64_t d = gcd(m, ms[i]);
        int64_t c = rs[i] - r;
        if (c % d)
            return -1;
        auto p = extend_gcd(m/d, ms[i]/d);
        int64_t k = (c / d * p.first) % (ms[i] / d);
        r = k * m + r;
        m = m / d * ms[i];
        r %= m;
    }
    while (r < 0)
        r += m;
    return r;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> ms(n), rs(n);
    for (int i = 0; i < n; ++i) {
        cin >> ms[i] >> rs[i];
    }
    cout << solve(ms, rs) << endl;
    return 0;
}
