#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int find(int i, vector<int> &vec)
{
    if (i != vec[i])
        vec[i] = find(vec[i], vec);
    return vec[i];
}

int main(void)
{
    int n;
    cin >> n;
    vector<int> vec(n);
    vector<string> names(n);
    unordered_map<string, int> dict;
    int k;
    string email;
    for (int i = 0; i < n; ++i) {
        vec[i] = i;
        cin >> names[i] >> k;
        for (int j = 0; j < k; ++j) {
            cin >> email;
            if (dict.find(email) == dict.end())
                dict[email] = i;
            else {
                int a = find(i, vec);
                int b = find(dict[email], vec);
                vec[max(a, b)] = min(a, b);
            }
        }
    }
    vector<vector<string>> groups;
    unordered_map<int, int> hash;
    for (int i = 0; i < n; ++i) {
        if (vec[i] == i) {
            hash[i] = groups.size();
            groups.push_back(vector<string>());
            groups[hash[i]].push_back(names[i]);
        } else {
            groups[hash[find(i, vec)]].push_back(names[i]);
        }
    }
    for (auto group : groups) {
        cout << group.front();
        for (int i = 1; i < group.size(); ++i)
            cout << " " << group[i];
        cout << "\n";
    }
    cout << flush;
    return 0;
}
