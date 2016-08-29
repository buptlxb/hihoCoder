#include <iostream>
#include <unordered_set>

using namespace std;

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    unordered_set<string> dict;
    string word;
    int ret = 0;
    for (int i = 0; i < n; ++i) {
        cin >> word;
        if (dict.erase(word))
            ++ret;
        else
            dict.emplace(word.rbegin(), word.rend());
    }
    cout << ret << endl;
    return 0;
}
