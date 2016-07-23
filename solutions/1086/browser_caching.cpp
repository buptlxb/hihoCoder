#include <iostream>
#include <map>
#include <list>

using namespace std;

map<string, int> hash;
map<int, list<int>::iterator> dict;
list<int> lru;
int index = 0;
int n, m;

int lru_hash(const string &url)
{
    if (hash.find(url) == hash.end())
        hash[url] = ++index;
    return hash[url];
}

bool lru_fetch(const string &url)
{
    int i = lru_hash(url);
    if (dict.find(i) == dict.end()) {
        if (dict.size() == m) {
            dict.erase(lru.back());
            lru.pop_back();
        }
        dict.insert(make_pair(i, lru.insert(lru.begin(), i)));
        return false;
    } else {
        lru.erase(dict[i]);
        dict[i] = lru.insert(lru.begin(), i);
        return true;
    }
}

int main(void)
{
    cin >> n >> m;
    string url;
    for (int i = 0; i < n; ++i) {
        cin >> url;
        cout << (lru_fetch(url) ? "Cache" : "Internet") << endl;
    }
    return 0;
}
