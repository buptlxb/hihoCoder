#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <unordered_map>

using namespace std;

inline void arrange(int w, int h, int &cw, int &ch)
{
    if (cw >= w) {
        cw -= w;
        ch = max(ch, h);
    } else {
        ch = max(ch, (cw * h + w - 1) / w);
        cw = 0;
    }
}

int solve(vector<int> &ws, vector<int> &hs, int m)
{
    int n = ws.size();
    vector<int> dp(n+1);
    for (int i = n-1; i >= 0; --i) {
        int cw = m, ch = 0;
        int j;
        for (j = i; j < n && cw; ++j) {
            arrange(ws[j], hs[j], cw, ch);
        }
        dp[i] = ch + dp[j];
    }
    int ret = dp[1];
    int cw = m, ch = 0, height = 0;
    for (int i = 0; i < n; ++i) {
        arrange(ws[i], hs[i], cw, ch);
        if (cw == 0) {
            cw = m;
            height += ch;
            ch = 0;
        }
        int j = i + 2, fw = cw, fh = ch;
        for ( ; j < n && fw; ++j) {
            arrange(ws[j], hs[j], fw, fh);
        }
        ret = min(ret, height + fh + (j < n ? dp[j] : 0));
    }
    return ret;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    cin >> m >> n;
    vector<int> ws(n), hs(n);
    for (int i = 0; i < n; ++i)
        cin >> ws[i] >> hs[i];
    cout << solve(ws, hs, m) << endl;
    return 0;
}
