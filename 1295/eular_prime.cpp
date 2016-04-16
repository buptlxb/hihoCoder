#include <iostream>
#include <vector>

using namespace std;

int primeCount(int n)
{
    vector<int> primes;
    vector<bool> is_prime(n+1, true);
    int ret = 0;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            ++ret;
            primes.push_back(i);
        }
        for (auto p : primes) {
            if (i * p > n)
                break;
            is_prime[i * p] = false;
            if (i % p == 0)
                break;
        }
    }
    return ret;
}

int main(void)
{
    int n;
    cin >> n;
    cout << primeCount(n) << endl;
    return 0;
}
