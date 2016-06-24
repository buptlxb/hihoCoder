#include <iostream>
#include <deque>
#include <utility>

using namespace std;

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    deque<pair<int, int>> q;
    deque<int> minq, maxq;
    int last = 0;
    while (n--) {
        char c; int t, p;
        cin >> c;
        if (c == 'P') {
            cin >> t >> p;
            last = p;
            q.push_back(make_pair(t, p));
            while (!minq.empty() && p < minq.back())
                minq.pop_back();
            minq.push_back(p);
            while (!maxq.empty() && p > maxq.back())
                maxq.pop_back();
            maxq.push_back(p);
        } else if (c == 'Q') {
            cout << maxq.front() << ' ' << minq.front() << ' ' << last << '\n';
        } else {
            cin >> t;
            while (q.front().first <= t) {
                if (q.front().second == minq.front())
                    minq.pop_front();
                if (q.front().second == maxq.front())
                    maxq.pop_front();
                q.pop_front();
            }
        }
    }
    cout << flush;
    return 0;
}
