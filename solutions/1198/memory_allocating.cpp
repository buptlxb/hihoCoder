#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

struct Chunk{
    int key;
    int length;
    Chunk *prev;
    Chunk *next;
    Chunk(int k=0, int len=0) : key(k), length(len), prev(nullptr), next(nullptr) {}
} *head;

void init(int m)
{
    Chunk *t = new Chunk(0, m);
    t->next = new Chunk(-1, 0);
    t->prev = new Chunk(-1, 0);
    t->next->prev = t;
    t->prev->next = t;
    head = t->prev;
}

Chunk *find_empty(int len)
{
    Chunk *p = head->next;
    for (Chunk *p = head->next; p->key != -1; p = p->next) {
        if (p->key == 0 && p->length >= len)
            return p;
    }
    return nullptr;
}

void insert(Chunk *p, int key, int len)
{
    assert(p->key == 0 && p->length >= len);
    if (p->length == len)
        p->key = key;
    else {
        Chunk *t = new Chunk(0, p->length-len);

        t->prev = p;
        t->next = p->next;
        t->next->prev = t;

        p->next = t;
        p->key = key;
        p->length = len;
    }
}

void release(Chunk *p)
{
    Chunk *t = p->prev;
    if (t->key == 0) {
        p->length += t->length;
        p->prev = t->prev;
        p->prev->next = p;
        delete t;
    }
    t = p->next;
    if (t->key == 0) {
        p->length += t->length;
        p->next = t->next;
        p->next->prev = p;
        delete t;
    }
    p->key = 0;
}

int main(void)
{
    int n, m;
    cin >> n >> m;
    init(m);
    vector<Chunk *> pos(n+1);
    for (int i = 1, last = 1; i <= n; ++i) {
        int k;
        cin >> k;
        while (true) {
            Chunk *p = find_empty(k);
            if (p) {
                insert(p, i, k);
                pos[i] = p;
                break;
            } else {
                release(pos[last]);
                pos[last++] = nullptr;
            }
        }
    }
    vector<pair<int, int>> res;
    int last = 0;
    for (Chunk *p = head->next; p->key != -1; p = p->next) {
        if (p->key)
            res.push_back(make_pair(p->key, last));
        last += p->length;
    }
    sort(res.begin(), res.end());
    for (auto &pr : res)
        cout << pr.first << " " << pr.second << '\n';
    cout << flush;
    return 0;
}
