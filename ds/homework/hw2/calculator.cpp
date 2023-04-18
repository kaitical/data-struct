#include <string>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include<stdio.h>
#include "../../stack/stack.h"
#include <cmath>
#include <stdexcept>
using namespace std;

#define M_PI 3.14159265358979323846

int get_priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^' ) return 4;
    if (op == 's' || op == 'c' || op == 't') return 3;
    if (op == '(') return 5;
    return 0;
}



bool is_operator(char op) {
    return op == '+' || op == '-' || op == '*' || op == '/' || op == '^' || op == 's' || op == 'c' || op == 't' 
        ;
}


double calculate(string s) {
    Stack<char> op_stack; // 操作符栈，存放运算符
    Stack<double> num_stack; // 操作数栈，存放数字
    int left_bracket_count = 0, right_bracket_count = 0; // 左括号和右括号的数量

    for (int i = 0; i < s.length(); i++) { // 遍历输入字符串
        char ch = s[i];
        if (isdigit(ch) || ch == '.') { // 如果是数字或小数点
            double num = 0.0;
            double decimal = 1.0; // 用于处理小数点后面的位数
            bool has_decimal = false; // 标记是否已经读取到小数点

            while (i < s.length() && (isdigit(s[i]) || s[i] == '.')) { // 持续读取数字和小数点
                if (s[i] == '.') {
                    if (has_decimal) { // 如果已经读取到小数点，则说明输入格式错误
                        cout << "Invalid Input: Multiple Decimal Points Found" << endl;
                        throw runtime_error("error:the calculation is illegal");
                    }
                    has_decimal = true; // 标记已经读取到小数点
                    i++;
                    continue; // 跳过小数点，进行下一次循环
                }
                if (!has_decimal) { // 如果还没有读取到小数点，则按照整数处理
                    num = num * 10 + (s[i] - '0');
                }
                else { // 如果已经读取到小数点，则按照小数处理
                    decimal *= 0.1;
                    num = num + (s[i] - '0') * decimal;
                }
                i++;
            }
            i--;
            num_stack.push(num); // 将得到的数字压入栈中
        }
        else if (is_operator(ch)) { // 如果是操作符
            if (i == s.length() - 1 || (is_operator(s[i + 1]) && s[i + 1] != '(' && s[i + 1] != 's' && s[i + 1] != 'c' && s[i + 1] != 't')) {
                // 如果当前操作符在表达式末尾，或下一个字符也为操作符且不是左括号和三角函数运算符，则算式有误
                throw runtime_error("error:the calculation is illegal");
            }
            if ((i == 0 && !isdigit(s[i + 1]) && s[i + 1] != '(' && s[i + 1] != 's' && s[i + 1] != 'c' && s[i + 1] != 't') ||
                (i > 0 && !isdigit(s[i - 1]) && s[i - 1] != ')' && s[i - 1] != 's' && s[i - 1] != 'c' && s[i - 1] != 't' && s[i - 1] != '^' && s[i - 1] != '(' && ch != '-')) {
                // 如果当前操作符在表达式开头且下一个字符也为操作符且不是数字、左括号和三角函数运算符，或者当前操作符前面的字符不是数字、右括号、三角函数运算符、指数运算符和左括号，并且当前操作符不是负号，则算式有误
                throw runtime_error("error:the calculation is illegal");
            }
            while (!op_stack.isEmpty() && op_stack.gettop() != '(' && get_priority(op_stack.gettop()) >= get_priority(ch)) {
                // 如果操作符栈不为空，且栈顶元素不为左括号，且栈顶操作符的优先级大于等于当前操作符的优先级
                char op = op_stack.gettop(); // 取出栈顶操作符
                op_stack.pop(); // 弹出栈顶操作符
                double num2 = num_stack.gettop(); // 取出栈顶数字作为运算的第二个操作数
                num_stack.pop(); // 弹出栈顶数字
                double num1 = 0.0;
                if (op != 's' && op != 'c' && op != 't') { // 如果是非三角函数运算符
                    num1 = num_stack.gettop(); // 取出次栈顶数字作为运算的第一个操作数
                    num_stack.pop(); // 弹出次栈顶数字
                }
                double result;
                switch (op) { // 根据操作符进行计算
                case '+':
                    result = num1 + num2;
                    break;
                case '-':
                    result = num1 - num2;
                    break;
                case '*':
                    result = num1 * num2;
                    break;
                case '/':
                    result = num1 / num2;
                    break;
                case '^':
                    result = pow(num1, num2);
                    break;
                case 's':
                    result = sin(num2 * M_PI / 180.0); // 将角度转化为弧度后进行计算
                    break;
                case 'c':
                    result = cos(num2 * M_PI / 180.0);
                    break;
                case 't':
                    result = tan(num2 * M_PI / 180.0);
                    break;
              
                }
                num_stack.push(result); // 将计算结果压入数字栈
            }
            op_stack.push(ch); // 将当前操作符压入操作符栈
        }
        else if (ch == '(') { // 如果是左括号，直接将其压入操作符栈，并更新左括号的数量
            op_stack.push(ch);
            left_bracket_count++;
        }
        else if (ch == ')') { // 如果是右括号
            right_bracket_count++; // 更新右括号的数量
            if (right_bracket_count > left_bracket_count) { // 如果右括号数大于左括号数，则算式有误
                throw runtime_error("error:the calculation is illegal");
            }
            while (!op_stack.isEmpty() && op_stack.gettop() != '(') { // 取出操作符栈顶的操作符并计算，直到遇到左括号为止
                char op = op_stack.gettop();
                op_stack.pop();
                double num2 = num_stack.gettop();
                num_stack.pop();
                double num1 = 0.0;
                if (op != 's' && op != 'c' && op != 't') {
                    num1 = num_stack.gettop();
                    num_stack.pop();
                }
                double result;
                switch (op) {
                case '+':
                    result = num1 + num2;
                    break;
                case '-':
                    result = num1 - num2;
                    break;
                case '*':
                    result = num1 * num2;
                    break;
                case '/':
                    result = num1 / num2;
                    break;
                case '^':
                    result = pow(num1, num2);
                    break;
                case 's':
                    result = sin(num2 * M_PI / 180.0);
                    break;
                case 'c':
                    result = cos(num2 * M_PI / 180.0);
                    break;
                case 't':
                    result = tan(num2 * M_PI / 180.0);
                    break;
               
                }
                num_stack.push(result);
            }
            if (!op_stack.isEmpty() && op_stack.gettop() == '(') { // 弹出左括号
                op_stack.pop();
            }
        }
    }

    if (left_bracket_count != right_bracket_count) { // 如果左右括号数量不匹配，则算式有误
        throw runtime_error("error:the calculation is illegal ");
    }

    while (!op_stack.isEmpty()) { // 当操作符栈不为空时，取出栈顶操作符并计算
        char op = op_stack.gettop();
        op_stack.pop();
        double num2 = num_stack.gettop();
        num_stack.pop();
        double num1 = 0.0;
        if (op != 's' && op != 'c' && op != 't') {
            num1 = num_stack.gettop();
            num_stack.pop();
        }
        double result;
        switch (op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            result = num1 / num2;
            break;
        case '^':
            result = pow(num1, num2);
            break;
        case 's':
            result = sin(num2 * M_PI / 180.0);
            break;
        case 'c':
            result = cos(num2 * M_PI / 180.0);
            break;
        case 't':
            result = tan(num2 * M_PI / 180.0);
            break;
       
        }
        num_stack.push(result); // 将计算结果压入数字栈
    }

    return num_stack.gettop(); // 返回数字栈顶元素，即计算结果
}
int main()	
{
    string input;
    cout<<"enter what you want to calculate(like (sin30+2*2-5^2/2)*2):"<<endl;
    getline(cin,input) ;
     input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
    try {
        cout << "the result is:" << calculate(input) << endl;
    }
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }
    return 0;}

