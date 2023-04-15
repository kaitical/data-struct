#pragma once
#include <iostream>
using namespace std;

#define MAX_SIZE 100

#define MAX_SIZE 100 // 定义最大容量

template<typename T> // 使用模板泛型，T为数据类型参数
class Stack {
private:
    int top; // 栈顶指针
    T arr[MAX_SIZE]; // 栈的数组实现

public:
    Stack() { // 构造函数，初始化栈顶为-1
        top = -1;
    }

    void push(T x) { // 入栈操作，将元素压入栈中
        if (top >= MAX_SIZE - 1) { // 栈已满
            cout << "Stack Overflow" << endl; // 输出提示信息
        }
        else { // 栈未满
            arr[++top] = x; // 栈顶指针加1，将元素压入栈中
        }
    }

    T pop() { // 出栈操作，从栈中弹出元素
        if (top < 0) { // 栈已空
            cout << "Stack Underflow" << endl; // 输出提示信息
            return T(); // 返回一个默认构造的类型T
        }
        else { // 栈未空
            return arr[top--]; // 返回栈顶元素并将栈顶指针减1
        }
    }

    T gettop() { // 获取栈顶元素
        if (top < 0) { // 栈已空
            cout << "Stack is empty" << endl; // 输出提示信息
            return T(); // 返回一个默认构造的类型T
        }
        else { // 栈未空
            return arr[top]; // 返回栈顶元素
        }
    }

    bool isEmpty() { // 判断栈是否为空
        return (top < 0); // 栈顶指针小于0则认为栈已空
    }
};