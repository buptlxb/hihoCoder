/*-------------------------------------------------------------------------
*    文件名  : resort.cpp
*    用  途  : 
*    创 建 者: buptlxb@gmail.com
*    创建时间: 2017年06月01日 20:26:10
*    修订记录: 
*-------------------------------------------------------------------------*/
#include <iostream>
#include <vector>

using namespace std;

int resort(vector<int> &indices) {
    int result = 0;
    do {
        if (indices.size() < 2)
            break;
        int head = 0;
        for (auto i = indices.size(); i > 1; --i) {
            // 对于数A和A-1，如果A的下标indices[A] < indices[A-1]，那么必须将A-1放在最左边
            if (indices[i-2] > indices[i-1]) {
                // head表示最左边的下标
                indices[i-2] = --head;
                ++result;
            }
        }
    } while (0);
    return result;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> indices(n);
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        indices[x-1] = i;
    }
    cout << resort(indices) << endl;
    return 0;
}
