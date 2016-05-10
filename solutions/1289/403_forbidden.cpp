#include <iostream>
#include <cassert>

using namespace std;

#define POOL_SIZE 3200005

class Trie {
    struct TrieNode {
        int order;
        TrieNode *children[2];
        TrieNode() : order(0) {}
    };
    TrieNode *root, *pool;
    int num;
    TrieNode *getTrieNode() {
        assert(num < POOL_SIZE);
        return pool + num++;
    }
public:
    Trie() : pool(new TrieNode[POOL_SIZE]), num(0) { root = getTrieNode(); }
    ~Trie() { delete[] pool; }
    void add(unsigned int ip, int mask, int order) {
        TrieNode *pos = root;
        for (int i = 0; i < mask; ++i) {
            if (pos->order)
                return;
            int bit = (ip >> (31 - i)) & 1;
            if (!pos->children[bit])
                pos->children[bit] = getTrieNode();
            pos = pos->children[bit];
        }
        if (!pos->order)
            pos->order = order;
    }
    int query(unsigned int ip) {
        TrieNode *pos = root;
        int order = 1;
        for (int i = 0; i < 32; ++i) {
            if (pos->order)
                order = pos->order;
            int bit = (ip >> (31 - i)) & 1;
            if (!pos->children[bit])
                break;
            pos = pos->children[bit];
        }
        return order;
    }
};

inline unsigned int getIp()
{
    unsigned int a, b, c, d;
    char t;
    cin >> a >> t >> b >> t >> c >> t >> d;
    return (a << 24) | (b << 16) | (c << 8) | d;
}

int main(void)
{
    int n, m;
    cin >> n >> m;
    Trie conf;
    string cmd;
    char t;
    for (int i = 1; i <= n; ++i) {
        cin >> cmd;
        unsigned int ip = getIp();
        int mask = 32;
        cin >> t;
        if (t == '/')
            cin >> mask;
        else
            cin.putback(t);
        int order = i;
        if (cmd != "allow")
            order *= -1;
        conf.add(ip, mask, order);
    }
    for (int i = 0; i < m; ++i) {
        unsigned int ip = getIp();
        cout << (conf.query(ip) < 0 ? "NO" : "YES") << endl;
    }
    return 0;
}
