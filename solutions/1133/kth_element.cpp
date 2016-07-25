#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int kth_element(vector<int>::iterator left, vector<int>::iterator kth, vector<int>::iterator right)
{
    int pivot = *left;
    vector<int>::iterator start = left, end = right--;
    while (left < right) {
        while (left < right && *right >= pivot)
            --right;
        if (left < right)
            *left++ = *right;
        while (left < right && *left < pivot)
            ++left;
        if (left < right)
            *right-- = *left;
    }
    *left = pivot;
    if (left == kth)
        return *kth;
    if (kth < left)
        return kth_element(start, kth, left);
    return kth_element(left+1, kth, end);
}

int main(void)
{
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i)
        cin >> nums[i];
    vector<int> nums2(nums);
    if (k < 1 || k >= n)
        cout << -1 << endl;
    else
        cout << kth_element(nums.begin(), nums.begin()+k-1, nums.end()) << endl;
    return 0;
}
