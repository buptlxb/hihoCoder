#include <iostream>
#include <iomanip>
#include <queue>
#include <cmath>

using namespace std;

struct Status {
    int a, b;
    double d;
    Status (int x, int y) : a(x), b(y) {
        d = (log(a+1) - log(a)) / b;
    }
};
bool operator< (const Status &lhs, const Status &rhs)
{
    return lhs.d < rhs.d;
}

int main(void)
{
    int n, k;
    cin >> n >> k;
    vector<int> A(k), B(k);
    for (int i = 0; i < k; ++i)
        cin >> A[i];
    for (int i = 0; i < k; ++i)
        cin >> B[i];
    priority_queue<Status> q;
    double res = 0;
    for (int i = 0; i < k; ++i) {
        res += log(A[i]) / B[i];
        q.emplace(A[i], B[i]);
    }
    for (int i = 0; i < n; ++i) {
        Status cur = q.top();
        q.pop();
        res += cur.d;
        q.emplace(cur.a+1, cur.b);
    }
    cout << fixed << setprecision(4) << exp(res) << endl;
    return 0;
}
