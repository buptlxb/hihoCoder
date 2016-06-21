#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

#define N 101
#define M 101

struct Node {
    Node *left, *right, *up, *down;
    int x, y;
    Node (int a=0, int b=0) : left(this), right(this), up(this), down(this), x(a), y(b) {}
    void reset() { left = this; right = this; up = this; down = this; }
} head;

Node columnHead[M];
Node *id[N][M];
vector<Node *> nodes;
int n, m;
int board[N][M];
int solution[N];

void init() {
    head.reset();
    memset(solution, 0, sizeof(solution));
}

void build() {
    Node *prev = &head;
    // chain the column head
    for (int i = 1; i <= m; ++i) {
        Node *p = &columnHead[i];
        p->reset();
        p->x = 0; p->y = i;
        p->right = prev->right;
        p->left = prev;
        prev->right->left = p;
        prev->right = p;
        prev = p;
    }
    // allocate node for every number one in board
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (!board[i][j])
                continue;
            id[i][j] = new Node(i, j);
            nodes.push_back(id[i][j]);
        }
    }
    // chain the column
    for (int j = 1; j <= m; ++j) {
        Node *prev = &columnHead[j];
        for (int i = 1; i <= n; ++i) {
            if (!board[i][j])
                continue;
            Node *p = id[i][j];
            p->down = prev->down;
            p->up = prev;
            prev->down->up = p;
            prev->down = p;
            prev = p;
        }
    }
    // chain the row
    for (int i = 1; i <= n; ++i) {
        Node *prev = nullptr;
        for (int j = 1; j <= m; ++j) {
            if (!board[i][j])
                continue;
            if (prev) {
                Node *p = id[i][j];
                p->right = prev->right;
                p->left = prev;
                prev->right->left = p;
                prev->right = p;
                prev = p;
            } else
                prev = id[i][j];
        }
    }
}

void detach(int idx)
{
    Node *p = &columnHead[idx];
    // detach the ith column head
    p->left->right = p->right;
    p->right->left = p->left;
    Node *p2 = p->down;
    while (p != p2) {
        Node *p3 = p2->right;
        // detach p3 row;
        while (p3 != p2) {
            p3->up->down = p3->down;
            p3->down->up = p3->up;
            p3 = p3->right;
        }
        p2 = p2->down;
    }
}

void resume(int idx)
{
    Node *p = &columnHead[idx];
    // resume the ith column head
    p->left->right = p;
    p->right->left = p;
    Node *p2 = p->down;
    while (p != p2) {
        Node *p3 = p2->right;
        while (p3 != p2) {
            p3->up->down = p3;
            p3->down->up = p3;
            p3 = p3->right;
        }
        p2 = p2->down;
    }
}

bool dance(int depth)
{
    Node *p = head.right;
    // cover all columns
    if (p == &head)
        return true;
    Node *p2 = p->down;
    // unable to cover current column
    if (p2 == p)
        return false;
    detach(p->y);
    while (p2 != p) {
        // select current row
        solution[depth] = p2->x;
        // detach columns cantained in the current row
        Node *p3 = p2->right;
        while (p3 != p2) {
            detach(p3->y);
            p3 = p3->right;
        }
        // depth first search
        if (dance(depth+1))
            return true;
        // reverse resume
        p3 = p2->left;
        while (p3 != p2) {
            resume(p3->y);
            p3 = p3->left;
        }
        p2 = p2->down;
    }
    resume(p->y);
    return false;
}

void fini()
{
    for (auto p : nodes)
        delete p;
    nodes.clear();
}

int main(void)
{
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                cin >> board[i][j];
            }
        }
        init();
        build();
        cout << (dance(0) ? "Yes" : "No") << endl;
        fini();
    }
    return 0;
}
