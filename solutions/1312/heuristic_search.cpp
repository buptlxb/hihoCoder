#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

struct Status {
    int order, step, estimate;
};

bool operator< (const Status &lhs, const Status &rhs)
{
    return lhs.step + lhs.estimate > rhs.step + rhs.estimate;
}

vector<int> uncantor(int, int&, int&);

ostream & operator<< (ostream & os, const Status &s)
{
    os << s.order << " "<< s.step << " "<< s.estimate << ":";
    int x, y;
    vector<int> permutation = uncantor(s.order, x, y);
    for (auto x : permutation)
        os << " " << x;
    os << " :" << x << " " << y;
    return os;
}

int cantor(const vector<int> &nums)
{
    static int base[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
    int ret = 0;
    for (int i = 0, iend = nums.size(); i < iend; ++i) {
        int a = 0;
        for (int j = i+1, jend = iend; j < jend; ++j)
            a += nums[i] > nums[j];
        ret += a * base[nums.size()-i-1];
    }
    return ret;
}

vector<int> uncantor(int order, int &x, int &y)
{
    vector<int> a(9), ret(9);
    vector<bool> used(9);
    static int base[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
    for (int i = 0; i < 9; ++i) {
        a[i] = order / base[9-i-1];
        order %= base[9-i-1];
        int cnt = 0;
        for (int j = 1; j <= 9; ++j) {
            if (used[j] || ++cnt != a[i] + 1)
                continue;
            ret[i] = j;
            used[j] = true;
            if (j == 9) {
                x = i / 3;
                y = i % 3;
            }
            break;
        }
    }
    return ret;
}

int manhattan(const vector<int> &nums)
{
    int ret = 0;
    for (int i = 0, iend = nums.size(); i < iend; ++i) {
        ret += abs(i/3 - (nums[i]-1)/3); // dx
        ret += abs(i%3 - (nums[i]-1)%3); // dy
    }
    return ret;
}

int solve(const vector<int> &nums)
{
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    priority_queue<Status> q;
    unordered_set<int> visited;
    Status start;
    start.order = cantor(nums);
    start.step = 0;
    start.estimate = manhattan(nums);
    q.push(start);
    visited.insert(start.order);
    while (!q.empty()) {
        Status cur = q.top();
        //cout << cur << endl;
        q.pop();
        if (cur.order == 0)
            return cur.step;
        int x, y;
        vector<int> permutation = uncantor(cur.order, x, y);
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || ny < 0 || nx > 2 || ny > 2)
                continue;
            swap(permutation[nx*3+ny], permutation[x*3+y]);
            int order = cantor(permutation);
            if (visited.find(order) == visited.end()) {
                Status neighbor;
                neighbor.order = order;
                neighbor.step = cur.step+1;
                neighbor.estimate = manhattan(permutation);
                q.push(neighbor);
                visited.insert(cur.order);
            }
            swap(permutation[nx*3+ny], permutation[x*3+y]);
        }
    }
    return -1;
}

int main(void)
{
    int t;
    cin >> t;
    vector<int> nums(9);
    while (t--) {
        for (int i = 0; i < 9; ++i) {
            cin >> nums[i];
            if (nums[i] == 0)
                nums[i] = 9;
        }
        int ret = solve(nums);
        if (ret >= 0)
            cout << ret << endl;
        else
            cout << "No Solution!" << endl;
    }
    return 0;
}
