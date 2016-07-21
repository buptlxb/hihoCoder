#include <iostream>
#include <algorithm>

using namespace std;

struct ICmp : equal_to<char> {
    bool operator() (const char &lhs, const char &rhs) {
        return tolower(lhs) == tolower(rhs);
    }
} icmp;

string &solve(string &line) {
    string a = "marshtomp", b = "fjxmlhx";
    for (auto i = line.begin(), iend = line.end(); i != iend; ++i) {
        if (equal(a.begin(), a.end(), i, icmp))
            line.replace(i, i+a.size(), b.begin(), b.end());
    }
    return line;
}

int main(void)
{
    string line;
    while (getline(cin, line)) {
        cout << solve(line) << endl;
    }
    return 0;
}
