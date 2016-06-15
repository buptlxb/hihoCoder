/**
 * 题目1 : 非法二进制数
 * 时间限制:10000ms
 * 单点时限:1000ms
 * 内存限制:256MB
 * 描述
 * 如果一个二进制数包含连续的两个1，我们就称这个二进制数是非法的。
 *
 * 小Hi想知道在所有 n 位二进制数（一共有2n个）中，非法二进制数有多少个。
 *
 * 例如对于 n = 3,有 011, 110, 111 三个非法二进制数。
 *
 * 由于结果可能很大，你只需要输出模109+7的余数。
 *
 * 输入
 * 一个整数 n (1 ≤ n ≤ 100)。
 *
 * 输出
 * n 位非法二进制数的数目模109+7的余数。
 *
 * 样例输入
 * 3
 * 样例输出
 * 3
 **/

#include <iostream>

using namespace std;

const int M = 1000000007;

int solve(int n)
{
    long long a = 0, b = 0, base = 1;
    for (int i = 1; i < n; ++i) {
        long long c = (a + b + base) % M;
        a = b;
        b = c;
        base = (base * 2) % M;
    }
    return b;
}

int main(void)
{
    int n;
    cin >> n; 
    cout << solve(n) << endl;
    return 0;
}
