#include <iostream>
#include <vector>

using namespace std;

struct TrieNode {
    vector<TrieNode *> children;
    size_t count;
    TrieNode () : children(26), count(0) {}
};

class Trie {
    TrieNode *root;
public:
    Trie() : root(new TrieNode()) {}
    ~Trie() { destory(root); }
    void add(const string &s) {
        TrieNode *p = root;
        p->count += 1;
        for (auto c : s) {
            if (!p->children[c2i(c)])
                p->children[c2i(c)] = new TrieNode();
            p = p->children[c2i(c)];
            p->count += 1;
        }
    }
    size_t prefix(const string &s) {
        TrieNode *p = root;
        for (auto c : s) {
            if (!p->children[c2i(c)])
                return 0;
            p = p->children[c2i(c)];
        }
        return p->count;
    }
private:
    Trie (const Trie &other);
    Trie operator= (const Trie &rhs);
    void destory(TrieNode *tn) {
        if (!tn)
            return;
        for (auto child : tn->children) {
            if (child)
                destory(child);
        }
        delete tn;
    }
    size_t c2i(char c) { return c - 'a'; }
};

int main(void)
{
    size_t n, m;
    string tmp;
    cin >> n;
    Trie t;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        t.add(tmp);
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> tmp;
        cout << t.prefix(tmp) << endl;
    }
    return 0;
}

