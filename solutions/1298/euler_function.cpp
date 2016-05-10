#include <iostream>
#include <vector>

using namespace std;

void euler(vector<int> &phi)
{
    vector<bool> is_prime(phi.size(), true);
    vector<int> prime_list;
    for (int i = 2, iend = is_prime.size(); i < iend; ++i) {
        if (is_prime[i]) {
            prime_list.push_back(i);
            phi[i] = i-1;
        }
        for (auto p : prime_list) {
            if (p * i >= iend)
                break;
            is_prime[p*i] = false;
            if (i % p == 0) {
                phi[i*p] = phi[i] * p;
                break;
            }  else {
                phi[i*p] = phi[i] * (p - 1);
            }
        }
    }
}

int solve(int L, int R)
{
    vector<int> phi(R+1, 0);
    euler(phi);
    phi[0] = R;
    int m = 0;
    for (int i = L; i <= R; ++i) {
        if (phi[m] > phi[i])
            m = i;
    }
    return m;
}

int main(void)
{
    int L, R;
    cin >> L >> R;
    cout << solve(L, R) << endl;
    return 0;
}
