#include <iostream>
#include <vector>

using namespace std;

bool dfs(vector<int>::size_type idx, const vector<int> &board, vector<bool> &landmines)
{
    int mine;
    if (idx == 1)
        mine = board[idx-1] - landmines[idx-1];
    else
        mine = board[idx-1] - landmines[idx-1] - landmines[idx-2];
    if (idx == board.size())
        return mine == 0;
    if (mine != 0 && mine != 1)
        return false;
    landmines[idx] = mine;
    return dfs(idx+1, board, landmines);
}

vector<int> solve(const vector<int> &board)
{
    vector<int> ret(board.size());
    vector<bool> landmines(board.size());
    landmines[0] = false;
    if (dfs(1, board, landmines)) {
        for (vector<int>::size_type i = 0, iend = board.size(); i < iend; ++i)
            ret[i] = landmines[i] ? 1 : -1;
    }
    landmines[0] = true;
    if (dfs(1, board, landmines)) {
        for (vector<int>::size_type i = 0, iend = board.size(); i < iend; ++i)
            if (ret[i] == 1 && !landmines[i] || ret[i] == -1 && landmines[i])
                ret[i] = 0;
            else if (ret[i] == 0)
                ret[i] = landmines[i] ? 1 : -1;
    }
    return ret;
}

int main(void)
{
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> board(n);
        for (int i = 0; i < n; ++i)
            cin >> board[i];
        vector<int> res = solve(board);
        int cnt = 0;
        for (auto x : res)
            if (x == 1)
                ++cnt;
        cout << cnt;
        for (vector<int>::size_type i = 0, iend = res.size(); i < iend; ++i)
            if (res[i] == 1)
                cout << " " << i+1;
        cout << endl;
        cnt = 0;
        for (auto x : res)
            if (x == -1)
                ++cnt;
        cout << cnt;
        for (vector<int>::size_type i = 0, iend = res.size(); i < iend; ++i)
            if (res[i] == -1)
                cout << " " << i+1;
        cout << endl;
    }
    return 0;
}
