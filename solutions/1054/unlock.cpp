#include <iostream>
#include <vector>
#include <utility>

using namespace std;

#define X(a) ((a)/3)
#define Y(a) ((a)%3)
#define MID(a, b) ((X(a) + X(b))/2*3 + (Y(a) + Y(b))/2)

bool collineation_check(int a, int b, const vector<bool> &visit)
{
    if (X(a) == X(b) && abs(Y(a)-Y(b)) == 2 && !visit[MID(a, b)])
        return false;
    if (Y(a) == Y(b) && abs(X(a)-X(b)) == 2 && !visit[MID(a, b)])
        return false;
    if (abs(X(a)-X(b)) == 2 && abs(Y(a)-Y(b)) == 2 && !visit[MID(a, b)])
        return false;
    return true;
}

bool degree_check(int a, int b, vector<vector<bool>> &path, vector<vector<bool>> &constraints)
{
    if (constraints[a][b])
        return true;
    int ad = 0, bd = 0;
    for (vector<bool>::size_type i = 0, iend = path[a].size(); i < iend; ++i) {
        ad += path[a][i] || constraints[a][i];
        bd += path[b][i] || constraints[b][i];
    }
    return ad < 2 && bd < 2;
}

bool integrity_check(vector<vector<bool>> &path, vector<vector<bool>> &constraints)
{
    for (vector<bool>::size_type i = 0, iend = path.size(); i < iend; ++i) {
        for (vector<bool>::size_type j = 0, jend = path[i].size(); j < jend; ++j) {
            if (constraints[i][j] && !path[i][j])
                return false;
        }
    }
    return true;
}

int dfs(int count, int digit, vector<vector<bool>> &path, vector<vector<bool>> &constraints, vector<bool> &visit, bool integrity)
{
    integrity = integrity || integrity_check(path, constraints);
    int ret = count >= 4 && integrity;
    for (int i = 0; i < 9; ++i) {
        if (visit[i] || !collineation_check(digit, i, visit) || !degree_check(digit, i, path, constraints))
            continue;
        visit[i] = path[digit][i] = path[i][digit] = true;
        ret += dfs(count+1, i, path, constraints, visit, integrity);
        visit[i] = path[digit][i] = path[i][digit] = false;
    }
    return ret;
}

int solve(vector<vector<bool>> &constraints)
{
    vector<bool> visit(9);
    vector<vector<bool>> path(9, vector<bool>(9));
    int cnt = 0;
    for (int i = 0; i < 9; ++i) {
        visit[i] = true;
        cnt += dfs(1, i, path, constraints, visit, false);
        visit[i] = false;
    }
    return cnt;
}

int main(void)
{
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        int n; cin >> n;
        vector<vector<bool>> constraints(9, vector<bool>(9));
        for (int j = 0; j < n; ++j) {
            int a, b;
            cin >> a >> b;
            constraints[a-1][b-1] = constraints[b-1][a-1] = true;
        }
        cout << solve(constraints) << endl;
    }
    return 0;
}
