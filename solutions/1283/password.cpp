#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
    int n;
    cin >> n;
    vector<int> passwd(n);
    for (int i = 0; i < n; ++i)
        cin >> passwd[i];
    if (n <= 2) {
        cout << passwd[0] << endl;
        return 0;
    }
    int i;
    for (i = n-1; i-1 >= 0; --i) {
        if (passwd[i] < passwd[i-1])
            break;
    }
    for (int j = 0; j < i; ++j)
        cout << passwd[j] << " ";
    cout << endl;
    return 0;
}
