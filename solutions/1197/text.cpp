#include <iostream>

using namespace std;

int main(void)
{
    char ch, p;
    string s;
    cin >> noskipws;
    while (cin >> ch) {
        // cout << ch << endl;
        if (isalpha(ch)) {
            s.push_back(tolower(ch));
            p = ch;
        } else if (ch != ' ' || isalpha(p) || ispunct(p)) {
            if (p == ' ' && ispunct(ch))
                s.back() = ch;
            else 
                s.push_back(ch);
            p = ch;
        }
    }
    bool start = true;
    string ret;
    for (auto c : s) {
        if (isalpha(c) && start) {
            c = toupper(c);
            start = false;
        } else if (c == '.')
            start = true;
        ret.push_back(c);
    }
    cout << ret;
    return 0;
}
