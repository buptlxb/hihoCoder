#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

int solve(string &s, int k)
{
    string::size_type n = s.size();
    int ret = 0;
    if (k*2 <= n) {
        for (string::size_type i = 0, j = s.size()-k; i < k; ++i, ++j)
            if (s[i] != s[j])
                ++ret;
    } else {
        string::size_type m = n - k;
        for (string::size_type i = 0; i < m; ++i) {
            vector<int> counts(4);
            for (string::size_type j = i; j < n; j += m) {
                switch(s[j]) {
                    case 'A':
                        ++counts[0];
                        break;
                    case 'C':
                        ++counts[1];
                        break;
                    case 'G':
                        ++counts[2];
                        break;
                    case 'T':
                        ++counts[3];
                        break;
                    default:
                        assert(0);
                }
                ++ret;
            }
            ret -= *max_element(counts.begin(), counts.end());
        }
    }
    return ret;
}

int main(void)
{
    int t;
    cin >> t;
    while (t--) {
        string s;
        int k;
        cin >> s >> k;
        cout << solve(s, k) << endl;
    }
    return 0;
}
