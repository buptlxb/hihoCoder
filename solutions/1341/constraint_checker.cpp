#include <iostream>
#include <functional>
#include <vector>

using namespace std;

struct Inequality {
    int lhs, rhs;
    function<bool(int, int)> op;
};

ostream &operator<< (ostream &os, const Inequality &iq)
{
    os << iq.lhs << typeid(iq.op).name() << iq.rhs;
    return os;
}

int value_of(int x, const vector<int> &assignment)
{
    return x > 'Z' ? x - 'Z' - 1 : assignment[x-'A'];
}

bool sat(const vector<Inequality> &constraints, const vector<int> &assignment)
{
    for (auto const &iq : constraints) {
        if (!iq.op(value_of(iq.lhs, assignment), value_of(iq.rhs, assignment)))
            return false;
    }
    return true;
}

int stoi(const string &s, string::size_type offset, string::size_type *idx, int base=10)
{
    int res = stoi(s.substr(offset), idx, base);
    *idx += offset;
    return res;
}

int parse(const string &s, vector<Inequality> &constraints, vector<int> &assignment)
{
    Inequality iq;
    string::size_type j = 0, jend = s.size(), symbols = 0;
    if (isupper(s[j])) {
        iq.lhs = s[j++];
        if (!assignment[iq.lhs-'A']) {
            ++symbols;
            assignment[iq.lhs-'A'] = 1;
        }
    } else
        iq.lhs = stoi(s, &j) + 'Z' + 1;
    for ( ;j < jend; ++j) {
        if (s[j] == '<')
            iq.op = less<int>();
        else if (s[j] == '=')
            iq.op = less_equal<int>();
        else {
            if (isupper(s[j])) {
                iq.rhs = s[j];
                if (!assignment[iq.rhs-'A']) {
                    ++symbols;
                    assignment[iq.rhs-'A'] = 1;
                }
            } else {
                iq.rhs = stoi(s, j, &j) + 'Z' + 1;
                --j;
            }
            constraints.push_back(iq);
            iq.lhs = iq.rhs;
        }
    }
    return symbols;
}

int main(void)
{
    int n;
    cin >> n;
    string s;
    vector<Inequality> constraints;
    vector<int> assignment(26);
    int symbols = 0;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        symbols += parse(s, constraints, assignment);
    }
    int t;
    cin >> t;
    char c; int val;
    for (int i = 0; i < t; ++i) {
        for (int j = 0; j < symbols; ++j) {
            cin >> c >> val;
            assignment[c-'A'] = val;
        }
        cout << (sat(constraints, assignment) ? "Yes" : "No") << endl;
    }
    return 0;
}
