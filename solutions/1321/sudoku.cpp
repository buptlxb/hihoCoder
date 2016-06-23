#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

#define N 9
#define NR_ROW (N*N*N)
#define NR_COL (4*N*N)

struct Node {
    Node *left, *right, *up, *down;
    int x, y;
    Node(int a=0, int b=0) : x(a), y(b), left(this), right(this), up(this), down(this) {}
    void reset() { left = right = up = down = this; }
} head;

int board[N][N];
int matrix[NR_ROW][NR_COL];
int count[NR_COL];
Node columnHead[NR_COL];
vector<Node *> nodes;
Node *id[NR_ROW][NR_COL];

int print()
{
    Node *p = head.right;
    int cnt = 0;
    while (&head != p) {
        ++cnt;
        p = p->right;
    }
    return cnt;
}

void set(int i, int j, int k)
{
    int id = i*9 + j;
    int pid = id*9 + k - 1;
    int t = i/3*3 + j/3;

    matrix[pid][i*9+k-1] = 1;
    matrix[pid][81+j*9+k-1] = 1;
    matrix[pid][162+t*9+k-1] = 1;
    matrix[pid][243+id] = 1;
}

void create()
{
    memset(matrix, 0, sizeof(matrix));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j])
                set(i, j, board[i][j]);
            else {
                for (int k = 1; k <= N; ++k)
                    set(i, j, k);
            }
        }
    }
}

void fini()
{
    for (auto p : nodes)
        delete p;
    nodes.clear();
}

void build()
{
    memset(count, 0, sizeof(count));
    Node *prev = &head;
    prev->reset();
    // chain column head
    for (int i = 0; i < NR_COL; ++i) {
        Node *p = &columnHead[i];
        p->reset();
        p->x = 0; p->y = i;
        p->right = prev->right;
        p->left = prev;
        prev->right->left = p;
        prev->right = p;
        prev = p;
    }
    // chain column
    for (int i = 0; i < NR_COL; ++i) {
        Node *p = &columnHead[i];
        for (int j = 0; j < NR_ROW; ++j) {
            if (!matrix[j][i])
                continue;
            ++count[i];
            id[j][i] = new Node(j, i);
            nodes.push_back(id[j][i]);
            id[j][i]->down = p->down;
            id[j][i]->up = p;
            p->down->up = id[j][i];
            p->down = id[j][i];
            p = p->down;
        }
    }
    // chain row
    for (int i = 0; i < NR_ROW; ++i) {
        Node *prev = nullptr;
        for (int j = 0; j < NR_COL; ++j) {
            if (!matrix[i][j])
                continue;
            if (prev) {
                id[i][j]->right = prev->right;
                id[i][j]->left = prev;
                prev->right->left = id[i][j];
                prev->right = id[i][j];
                prev = prev->right;
            } else
                prev = id[i][j];
        }
    }
}

void detach(int idx)
{
    Node *p = &columnHead[idx];
    p->right->left = p->left;
    p->left->right = p->right;
    Node *p2 = p->down;
    while (p != p2) {
        Node *p3 = p2->right;
        while (p2 != p3) {
            --count[p3->y];
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
    p->right->left = p;
    p->left->right = p;
    Node *p2 = p->down;
    while (p != p2) {
        Node *p3 = p2->right;
        while (p2 != p3) {
            ++count[p3->y];
            p3->up->down = p3;
            p3->down->up = p3;
            p3 = p3->right;
        }
        p2 = p2->down;
    }
}

bool dance()
{
    Node *p = head.right;
    if (p == &head)
        return true;

    Node *p2 = p;
    while (&head != p2) {
        if (count[p->y] > count[p2->y])
            p = p2;
        p2 = p2->right;
    }
    p2 = p->down;
    if (p2 == p)
        return false;
    detach(p->y);
    while (p != p2) {
        Node *p3 = p2->right;
        while (p3 != p2) {
            detach(p3->y);
            p3 = p3->right;
        }
        board[p2->x/81][p2->x/9%9] = p2->x % 9 + 1;
        if (dance())
            return true;
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

using namespace std;

int main(void)
{
    int t;
    cin >> t;
    while (t--) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> board[i][j];
            }
        }
        create();
        build();
        if (dance()) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    cout << board[i][j] << " ";
                }
                cout << endl;
            }
        } else
            cout << "No solution" << endl;
        fini();
    }
    return 0;
}
