#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string::size_type solve_tle(const string &s)
{
    string::size_type npld = 0;
    vector<vector<bool>> dp(s.size(), vector<bool>(s.size()));
    for (string::size_type i = 0, iend = s.size(); i!= iend; ++i) {
        for (string::size_type j = 0, jend = iend-i; j < jend; ++j) {
            if (s[j] == s[j+i] && (i < 2 || dp[i-2][j+1])) {
                dp[i][j] = true;
                npld = max(npld, i+1);
            }
        }
    }
    return npld;
}

string::size_type solve(const string &s)
{
    if (s.size() < 2)
        return s.size();
    vector<char> ns;
    ns.reserve(s.size()*2 + 3);
    ns.push_back('^');
    ns.push_back('#');
    for (auto c : s) {
        ns.push_back(c);
        ns.push_back('#');
    }
    ns.push_back('$');
    vector<string::size_type> radius(ns.size(), 1);
    vector<char>::size_type mid = 0, reach = 0;
    for (vector<char>::size_type i = 1, iend = ns.size()-1; i < iend; ++i) {
        radius[i] = i < reach ? min(reach-i, radius[2*mid - i]) : 1;
        while (ns[i-radius[i]] == ns[i+radius[i]])
            ++radius[i];
        if (radius[i] + i > reach) {
            mid = i;
            reach = mid + radius[i];
        }
    }
    return *max_element(radius.begin(), radius.end()) - 1;
}

int main(void)
{
    int n;
    string s;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        cout << solve(s) << endl;
    }
    return 0;
}

