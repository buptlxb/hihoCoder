#include <iostream>
#include <cassert>

using namespace std;

typedef string::const_iterator Iter;

string getPostorder(Iter pb, Iter pe, Iter ib, Iter ie)
{
    if (pb == pe) {
        assert(ib == ie);
        return "";
    }
    Iter im = ib;
    while (im != ie && *pb != *im)
        ++im;
    assert(im != ie);
    return getPostorder(pb+1, pb+(im-ib)+1, ib, im) + getPostorder(pb+(im-ib)+1, pe, im+1, ie) + *pb;
}

string getPostorder(const string &preorder, const string &inorder)
{
    return getPostorder(preorder.begin(), preorder.end(), inorder.begin(), inorder.end());
}

int main(void)
{
    string preorder, inorder;
    while (cin >> preorder >> inorder) {
        cout << getPostorder(preorder, inorder) << endl;
    }
    return 0;
}
