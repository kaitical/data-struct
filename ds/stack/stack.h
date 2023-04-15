#pragma once
#include <iostream>
using namespace std;

#define MAX_SIZE 100

#define MAX_SIZE 100 // �����������

template<typename T> // ʹ��ģ�巺�ͣ�TΪ�������Ͳ���
class Stack {
private:
    int top; // ջ��ָ��
    T arr[MAX_SIZE]; // ջ������ʵ��

public:
    Stack() { // ���캯������ʼ��ջ��Ϊ-1
        top = -1;
    }

    void push(T x) { // ��ջ��������Ԫ��ѹ��ջ��
        if (top >= MAX_SIZE - 1) { // ջ����
            cout << "Stack Overflow" << endl; // �����ʾ��Ϣ
        }
        else { // ջδ��
            arr[++top] = x; // ջ��ָ���1����Ԫ��ѹ��ջ��
        }
    }

    T pop() { // ��ջ��������ջ�е���Ԫ��
        if (top < 0) { // ջ�ѿ�
            cout << "Stack Underflow" << endl; // �����ʾ��Ϣ
            return T(); // ����һ��Ĭ�Ϲ��������T
        }
        else { // ջδ��
            return arr[top--]; // ����ջ��Ԫ�ز���ջ��ָ���1
        }
    }

    T gettop() { // ��ȡջ��Ԫ��
        if (top < 0) { // ջ�ѿ�
            cout << "Stack is empty" << endl; // �����ʾ��Ϣ
            return T(); // ����һ��Ĭ�Ϲ��������T
        }
        else { // ջδ��
            return arr[top]; // ����ջ��Ԫ��
        }
    }

    bool isEmpty() { // �ж�ջ�Ƿ�Ϊ��
        return (top < 0); // ջ��ָ��С��0����Ϊջ�ѿ�
    }
};