#include <iostream>
#include <unordered_set>
#include <iomanip>

using namespace std;

double f1_score(int tp, int fp, int fn, int tn) {
    return 1.0 * tp / (2*tp + fp + fn) * 200;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    int tp(0), fp(0), fn(0), tn(0);
    string answer, predict;
    for (int i = 0; i < n; ++i) {
        cin >> answer >> predict;
        if (answer == "+") {
            if (answer == predict)
                ++tp;
            else
                ++fn;
        } else {
            if (answer == predict)
                ++tn;
            else
                ++fp;
        }
    }
    cout << fixed << setprecision(2) << f1_score(tp, fp, fn, tn) << "%" << endl;
    return 0;
}
