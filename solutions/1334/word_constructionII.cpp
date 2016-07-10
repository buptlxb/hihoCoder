#include <iostream>
#include <stack>

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

int board[M][N];
Node *id[M][N];
Node colHead[N];
bool join[N];

void build()
{
    Node *prev = head;
    for (int i = 0; i < n; ++i) {
        join[i] = true;
        Node *p = colHead + i;
        p->right = prev->right;
        p->left = prev;
        prev->right->left = p;
        prev->right = p;
        p->y = i;
        prev = p;
    }
    for (int i = 0; i < n; ++i) {
        Node *prev = &colHead[i];
        for (int j = 0; j < M; ++j) {
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
    for (int i = 0; i < M; ++i) {
        Node *prev = nullptr;
        for (int j = 0; j < n; ++j) {
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
    if (!join[y])
        return;

    Node *p = &colHead[y];
    do {
        p->right->left = p->left;
        p->left->right = p->right;
        p = p->down;
    } while (p != &colHead[y]);

    join[y] = false;
}

void resume(int y)
{
    if (join[y])
        return;

    Node *p = &colHead[y];
    do {
        p->right->left = p;
        p->left->right = p;
        p = p->down;
    } while (p != &colHead[y]);

    join[y] = true;
}

int res[N];

int dance(int cnt)
{
    int ret = cnt;
    for (Node *p = head->right; p != head; p = p->right) {
        res[cnt] = p->y;
        stack<Node *> s;
        for (Node *q = p->down; q != p; q = q->down) {
            Node *r = q->right;
            while (r != q) {
                s.push(r);
                detach(r->y);
                r = r->right;
            }
        }
        detach(p->y);
        ret = max(ret, dance(cnt + 1));
        while (!s.empty()) {
            resume(s.top()->y);
            s.pop();
        }
        resume(p->y);
    }
    // if (head->right == head) {
    //     for (int i = 0; i < ret; ++i) {
    //         cout << words[res[i]] << endl;
    //     }
    //     cout << " ============== "<< endl;
    // }
    return ret;
}


int main(void)
{
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> words[i];
        for (auto c : words[i]) {
            board[c-'a'][i] = 1;
        }
    }
    build();
    int r = dance(0);
    cout << r << endl;
    //for (int i = 0; i < r; ++i)
    //    cout << words[res[i]] << endl;
}
