#include <iostream>
#include <cassert>

using namespace std;

#define MIN3(x, y, z) min((x), min((y), (z)))
#define MAX3(x, y, z) max((x), max((y), (z)))
#define MID3(x, y, z) ((x)-MIN3(x, y, z)+(y)+(z)-MAX3(x, y, z))

bool check(int x1, int y1, int z1, int x2, int y2, int z2)
{
    if (MIN3(x1, y1, z1) == MIN3(x2, y2, z2) && MAX3(x1, y1, z1) == MAX3(x2, y2, z2) && MID3(x1, y1, z1) == MID3(x2, y2, z2))
        return true;
    return false;
}

int main(void)
{
    int x, y, z;
    cin >> x >> y >> z;
    int cr = 0, cy = 0, cb = 0;
    string str;
    cin >> str;
    int cnt = 0, m = 0;
    for (auto c : str) {
        ++cnt;
        if (c == 'R')
            ++cr;
        else if (c == 'Y')
            ++cy;
        else if (c == 'B')
            ++cb;
        else
            assert(0);
        m = max(m, cnt);
        if (check(abs(cr-cy), abs(cy-cb), abs(cb-cr), x, y, z)) {
            cnt = cr = cy = cb = 0;
        }
    }
    cout << m << endl;
    return 0;
}
