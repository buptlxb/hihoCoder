#include <iostream>
#include <sstream>
#include <stack>
#include <cassert>

using namespace std;

bool weak(char lhs, char rhs)
{
    if (rhs == '*' || rhs == '/')
        return true;
    if (lhs == '*' || lhs == '/' || rhs == '(')
        return false;
    return true;
}

void calc(stack<int> &operands, stack<char> &operators)
{
    int rhs = operands.top(); operands.pop();
    int lhs = operands.top(); operands.pop();
    switch (operators.top()) {
        case '+':
            operands.push(lhs + rhs);
            break;
        case '-':
            operands.push(lhs - rhs);
            break;
        case '*':
            operands.push(lhs * rhs);
            break;
        case '/':
            operands.push(lhs / rhs);
            break;
        default:
            assert(0);
    }
    operators.pop();
}

int solve(string &str)
{
    stack<int> operands;
    stack<char> operators;
    istringstream is(str);
    ostringstream os;
    for (string::size_type i = 0, iend = str.size(); i < iend; ) {
        if (isdigit(str[i])) {
            int num = 0;
            while (i < iend && isdigit(str[i])) {
                num = num * 10 +  str[i] - '0';
                ++i;
            }
            operands.push(num);
        } else {
            char op = str[i++];
            if (op == ')') {
                while (operators.top() != '(') {
                    calc(operands, operators);
                }
                operators.pop();
            } else if (op != '(') {
                while (!operators.empty() && weak(op, operators.top())) {
                    calc(operands, operators);
                }
                operators.push(op);
            } else 
                operators.push(op);
        }
    }
    while (!operators.empty()) {
        calc(operands, operators);
    }
    return operands.top();
}

int main(void)
{
    string str;
    cin >> str;
    cout << solve(str) << endl;
    return 0;
}
