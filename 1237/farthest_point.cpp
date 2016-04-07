#include <iostream>
#include <cmath>

using namespace std;

inline double dist(double x0, double y0, double x1, double y1)
{
    return (x0-x1)*(x0-x1) + (y0-y1)*(y0-y1);
}

void solve(double x, double y, double r, int &ix, int &iy)
{
    double m = 0;
    for (int i = floor(x+r), iend = ceil(x-r); i >= iend; --i) {
        int j = floor(y + sqrt(r*r - (i-x)*(i-x)));
        double t = dist(i, j, x, y);
        if (t > m) {
            ix = i;
            iy = j;
            m = t;
        }
        j = ceil(y - sqrt(r*r - (i-x)*(i-x)));
        t = dist(i, j, x, y);
        if (t > m) {
            ix = i;
            iy = j;
            m = t;
        }
    }
}

int main(void)
{
    double x, y, r;
    while (cin >> x >> y >> r) {
       int ix, iy;
       solve(x, y, r, ix, iy);
       cout << ix << " " << iy << endl;
    }
    return 0;
}
