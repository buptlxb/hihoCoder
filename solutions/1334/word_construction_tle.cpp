#include <iostream>

using namespace std;

#define N 40
#define M 26

string words[N];
int n;

struct Node {
    int x, y;
    Node *up, *down, *left, *right;
    Node (int a=0, int b=0) : x(a), y(b), up(this), down(this), left(this), right(this) {}
    void reset() {
        up = down = left = right = this;
    }
} dummy, *head = &dummy;

int board[N][M];
Node *id[N][M];
Node colHead[M];

void build()
{
    Node *prev = head;
    for (int i = 0; i < M; ++i) {
        Node *p = colHead + i;
        p->right = prev->right;
        p->left = prev;
        prev->right->left = p;
        prev->right = p;
        p->y = i;
        prev = p;
    }
    for (int i = 0; i < M; ++i) {
        Node *prev = &colHead[i];
        for (int j = 0; j < n; ++j) {
            if (board[j][i] == 0)
                continue;
            Node *p = id[j][i] = new Node(j, i);
            p->down = prev->down;
            p->up = prev;
            prev->down->up = p;
            prev->down = p;
            prev = p;
        }
    }
    for (int i = 0; i < n; ++i) {
        Node *prev = nullptr;
        for (int j = 0; j < M; ++j) {
            if (board[i][j] == 0)
                continue;
            Node *p = id[i][j];
            if (prev) {
                p->right = prev->right;
                p->left = prev;
                prev->right->left = p;
                prev->right = p;
                prev = p;
            } else
                prev = p;
        }
    }
}

void detach(int y)
{
    Node *p = &colHead[y];
    p->right->left = p->left;
    p->left->right = p->right;
    Node *q = p->down;
    while (q != p) {
        Node *prev = q->right;
        while (prev != q) {
            prev->down->up = prev->up;
            prev->up->down = prev->down;
            prev = prev->right;
        }
        q = q->down;
    }
}

void resume(int y)
{
    Node *p = &colHead[y];
    p->right->left = p;
    p->left->right = p;
    Node *q = p->down;
    while (q != p) {
        Node *prev = q->right;
        while (prev != q) {
            prev->down->up = prev;
            prev->up->down = prev;
            prev = prev->right;
        }
        q = q->down;
    }
}

int dance(int cnt)
{
    int ret = cnt;
    for (Node *p = head->right; p != head; p = p->right) {
        detach(p->y);
        for (Node *q = p->down; q != p; q = q->down) {
            Node *r = q->right;
            while (r != q) {
                detach(r->y);
                r = r->right;
            }
            ret = max(ret, dance(cnt + 1));
            r = q->left;
            while (r != q) {
                resume(r->y);
                r = r->left;
            }
        }
        resume(p->y);
    }
    return ret;
}


int main(void)
{
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> words[i];
        for (auto c : words[i]) {
            board[i][c-'a'] = 1;
        }
    }
    build();
    cout << dance(0) << endl;
}
