#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int query(vector<int> &weights, int first, int last)
{
    return *min_element(weights.begin()+first, weights.begin()+last);
}

int main(void)
{
    int n;
    cin >> n;
    vector<int> weights(n);
    for (int i = 0; i < n; ++i)
        cin >> weights[i];
    int q, a, b, c;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> a >> b >> c;
        if (a)
            weights[b-1] = c;
        else
            cout << query(weights, b-1, c) << endl;
    }
    return 0;
}
