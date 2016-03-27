#include <iostream>
#include <vector>
#include <string>

using namespace std;

size_t count(const string &str, const string &pattern)
{
    if (pattern.size() == 0 || str.size() < pattern.size())
        return 0;
    vector<int> next(pattern.size() + 1);
    next[0] = -1;
    next[1] = 0;
    for (string::size_type i = 1; i < pattern.size(); ++i) {
        for (int j = next[i]; j != -1; j = next[j]) {
            if (pattern[j] == pattern[i]) {
                next[i+1] = j + 1;
                break;
            }
        }
    }
    size_t cnt = 0;
    int i = 0, j = 0;
    while (i < str.size()) {
        if (j == -1 || str[i] == pattern[j]) {
            ++i;
            ++j;
            if (j == pattern.size()) {
                ++cnt;
                j = next[j];
            }
        } else {
            j = next[j];
        }
    }
    return cnt;
}

int main(void)
{
    int n;
    cin >> n;
    string pattern, str;
    for (int i = 0; i < n; ++i) {
        cin >> pattern >> str;
        cout << count(str, pattern) << endl;
    }
    return 0;
}

