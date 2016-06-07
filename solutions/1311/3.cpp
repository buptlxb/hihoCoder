#include <iostream>

using namespace std;

int mul(string &num, int x)
{
    int carry = 0;
    for (string::size_type i = num.size(); i > 0; --i) {
        int tmp = carry + (num[i-1]-'0') * x;
        num[i-1] = tmp % 10 + '0';
        carry = tmp / 10;
    }
    while (num.back() == '0')
        num.pop_back();
    return carry;
}

string solve(string &s)
{
    string num(s.begin()+2, s.end());
    string ret("0.");
    while (num.size()) {
        if (num.back() != '5')
            return "NO";
        ret.push_back(mul(num, 2) + '0');
    }
    return ret;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    string d;
    while (t--) {
        cin >> d;
        cout << solve(d) << '\n';
    }
    return 0;
}
