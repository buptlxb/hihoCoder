#include <iostream>
#include <vector>

using namespace std;

int solve(vector<vector<char>> &maze)
{
    const int n = maze.size();
    const int m = maze.front().size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(2)));
    dp[0][0][0] = maze[0][0] == 'b';
    dp[0][0][1] = dp[0][0][0] + (1 < m && maze[0][1] != 'b');
    for (int i = 1; i < n; ++i) {
        dp[i][0][1] = min(dp[i-1][0][0] + (1 < m && maze[i-1][1] != 'b'), dp[i-1][0][1]) + (maze[i][0] == 'b');
        dp[i][0][0] = dp[i][0][1] + (i+1 < n && maze[i+1][0] != 'b');
    }
    for (int i = 1; i < m; ++i) {
        dp[0][i][0] = min(dp[0][i-1][1] + (1 < n && maze[1][i-1] != 'b'), dp[0][i-1][0]) + (maze[0][i] == 'b');
        dp[0][i][1] = dp[0][i][0] + (i+1 < m && maze[0][i+1] != 'b');
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            dp[i][j][0] = min(dp[i][j-1][0], dp[i-1][j][1] + (i+1 < n && maze[i+1][j] != 'b')) + (maze[i][j] == 'b');
            dp[i][j][1] = min(dp[i-1][j][1], dp[i][j-1][0] + (j+1 < m && maze[i][j+1] != 'b')) + (maze[i][j] == 'b');
        }
    }
    return min(dp[n-1][m-1][0], dp[n-1][m-1][1]);
}

int main(void)
{
    int n, m;
    while (cin >> n >> m) {
        vector<vector<char>> maze(n, vector<char>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> maze[i][j];
            }
        }
        cout << solve(maze) << endl;
    }
}
