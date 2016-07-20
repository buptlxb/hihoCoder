#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <functional>

using namespace std;
struct Friend{
    long long a, b;
    bool flag;
    Friend() : a(0), b(0), flag(false) {}
};

struct FriendLess1 : less<Friend> {
    bool operator() (const Friend &lhs, const Friend &rhs) const {
        return lhs.b < rhs.b || lhs.b == rhs.b && lhs.a > rhs.a;
    }
} fls1;

struct FriendLess2 : less<Friend> {
    bool operator() (const Friend &lhs, const Friend &rhs) const {
        return lhs.a > rhs.a || lhs.a == rhs.a && lhs.b > rhs.b;
    }
} fls2;

struct FriendPlus : plus<Friend> {
    Friend operator() (const Friend &lhs, const Friend &rhs) {
        Friend tmp;
        tmp.a = lhs.a + rhs.a;
        tmp.b = lhs.b + rhs.b;
        return tmp;
    }
} fps;

int main(void)
{
    int n, p, k;
    cin >> n >> p >> k;
    vector<Friend> friends(n);
    for (int i = 0; i < n; ++i) {
        cin >> friends[i].a >> friends[i].b;
    }
    partial_sort(friends.begin(), p-k+friends.begin(), friends.end(), fls1);
    partial_sort(p-k+friends.begin(), p+friends.begin(), friends.end(), fls2);

    Friend res;
    res = accumulate(p-k+friends.begin(), p+friends.begin(), res, fps);
    for (auto i = p-k+friends.begin(), iend = p+friends.begin(); i != iend; ++i)
        i->flag = true;

    sort(friends.begin(), friends.end(), fls1);
    for (auto i = friends.begin(), j = p-k+i, iend = friends.end(); j != iend; ++i, ++j) {
        if (j->flag) {
            res = accumulate(i, j, res, fps);
            break;
        }
    }
    cout << res.a << " " << res.b << endl;
    return 0;
}
