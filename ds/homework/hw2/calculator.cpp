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
    Stack<char> op_stack; // ������ջ����������
    Stack<double> num_stack; // ������ջ���������
    int left_bracket_count = 0, right_bracket_count = 0; // �����ź������ŵ�����

    for (int i = 0; i < s.length(); i++) { // ���������ַ���
        char ch = s[i];
        if (isdigit(ch) || ch == '.') { // ��������ֻ�С����
            double num = 0.0;
            double decimal = 1.0; // ���ڴ���С��������λ��
            bool has_decimal = false; // ����Ƿ��Ѿ���ȡ��С����

            while (i < s.length() && (isdigit(s[i]) || s[i] == '.')) { // ������ȡ���ֺ�С����
                if (s[i] == '.') {
                    if (has_decimal) { // ����Ѿ���ȡ��С���㣬��˵�������ʽ����
                        cout << "Invalid Input: Multiple Decimal Points Found" << endl;
                        throw runtime_error("error:the calculation is illegal");
                    }
                    has_decimal = true; // ����Ѿ���ȡ��С����
                    i++;
                    continue; // ����С���㣬������һ��ѭ��
                }
                if (!has_decimal) { // �����û�ж�ȡ��С���㣬������������
                    num = num * 10 + (s[i] - '0');
                }
                else { // ����Ѿ���ȡ��С���㣬����С������
                    decimal *= 0.1;
                    num = num + (s[i] - '0') * decimal;
                }
                i++;
            }
            i--;
            num_stack.push(num); // ���õ�������ѹ��ջ��
        }
        else if (is_operator(ch)) { // ����ǲ�����
            if (i == s.length() - 1 || (is_operator(s[i + 1]) && s[i + 1] != '(' && s[i + 1] != 's' && s[i + 1] != 'c' && s[i + 1] != 't')) {
                // �����ǰ�������ڱ��ʽĩβ������һ���ַ�ҲΪ�������Ҳ��������ź����Ǻ��������������ʽ����
                throw runtime_error("error:the calculation is illegal");
            }
            if ((i == 0 && !isdigit(s[i + 1]) && s[i + 1] != '(' && s[i + 1] != 's' && s[i + 1] != 'c' && s[i + 1] != 't') ||
                (i > 0 && !isdigit(s[i - 1]) && s[i - 1] != ')' && s[i - 1] != 's' && s[i - 1] != 'c' && s[i - 1] != 't' && s[i - 1] != '^' && s[i - 1] != '(' && ch != '-')) {
                // �����ǰ�������ڱ��ʽ��ͷ����һ���ַ�ҲΪ�������Ҳ������֡������ź����Ǻ�������������ߵ�ǰ������ǰ����ַ��������֡������š����Ǻ����������ָ��������������ţ����ҵ�ǰ���������Ǹ��ţ�����ʽ����
                throw runtime_error("error:the calculation is illegal");
            }
            while (!op_stack.isEmpty() && op_stack.gettop() != '(' && get_priority(op_stack.gettop()) >= get_priority(ch)) {
                // ���������ջ��Ϊ�գ���ջ��Ԫ�ز�Ϊ�����ţ���ջ�������������ȼ����ڵ��ڵ�ǰ�����������ȼ�
                char op = op_stack.gettop(); // ȡ��ջ��������
                op_stack.pop(); // ����ջ��������
                double num2 = num_stack.gettop(); // ȡ��ջ��������Ϊ����ĵڶ���������
                num_stack.pop(); // ����ջ������
                double num1 = 0.0;
                if (op != 's' && op != 'c' && op != 't') { // ����Ƿ����Ǻ��������
                    num1 = num_stack.gettop(); // ȡ����ջ��������Ϊ����ĵ�һ��������
                    num_stack.pop(); // ������ջ������
                }
                double result;
                switch (op) { // ���ݲ��������м���
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
                    result = sin(num2 * M_PI / 180.0); // ���Ƕ�ת��Ϊ���Ⱥ���м���
                    break;
                case 'c':
                    result = cos(num2 * M_PI / 180.0);
                    break;
                case 't':
                    result = tan(num2 * M_PI / 180.0);
                    break;
              
                }
                num_stack.push(result); // ��������ѹ������ջ
            }
            op_stack.push(ch); // ����ǰ������ѹ�������ջ
        }
        else if (ch == '(') { // ����������ţ�ֱ�ӽ���ѹ�������ջ�������������ŵ�����
            op_stack.push(ch);
            left_bracket_count++;
        }
        else if (ch == ')') { // �����������
            right_bracket_count++; // ���������ŵ�����
            if (right_bracket_count > left_bracket_count) { // �����������������������������ʽ����
                throw runtime_error("error:the calculation is illegal");
            }
            while (!op_stack.isEmpty() && op_stack.gettop() != '(') { // ȡ��������ջ���Ĳ����������㣬ֱ������������Ϊֹ
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
            if (!op_stack.isEmpty() && op_stack.gettop() == '(') { // ����������
                op_stack.pop();
            }
        }
    }

    if (left_bracket_count != right_bracket_count) { // �����������������ƥ�䣬����ʽ����
        throw runtime_error("error:the calculation is illegal ");
    }

    while (!op_stack.isEmpty()) { // ��������ջ��Ϊ��ʱ��ȡ��ջ��������������
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
        num_stack.push(result); // ��������ѹ������ջ
    }

    return num_stack.gettop(); // ��������ջ��Ԫ�أ���������
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

