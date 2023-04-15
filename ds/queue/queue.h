#pragma once
#include <iostream>
#define MAX_SIZE 10  // ������󳤶�

class Queue {
private:
    int head;  // ͷָ�룬��ʼʱΪ0
    int tail;  // βָ�룬��ʼʱΪ0
    int arr[MAX_SIZE];  // ������洢����Ԫ��
public:
    Queue() {  // ���캯��
        head = tail = 0;
    }
    // �ж϶����Ƿ�Ϊ��
    bool is_empty() {
        return head == tail;
    }
    // �ж϶����Ƿ�����
    bool is_full() {
        return (tail + 1) % MAX_SIZE == head;
    }
    // Ԫ�������
    bool enqueue(int x) {
        if (is_full()) {
            std::cout << "Queue is full, cannot enqueue element." << std::endl;
            return false;
        }
        arr[tail] = x;
        tail = (tail + 1) % MAX_SIZE;  // ��βָ�����ȡģ��ȷ����Ԫ�ؼ��������
        return true;
    }
    // Ԫ�س�����
    bool dequeue() {
        if (is_empty()) {
            std::cout << "Queue is empty, cannot dequeue element." << std::endl;
            return false;
        }
        head = (head + 1) % MAX_SIZE;  // ͷָ���ƶ���������һ��Ԫ��
        return true;
    }
    // ��ȡ��ͷԪ��
    int front() {
        if (is_empty()) {
            std::cout << "Queue is empty, no front element." << std::endl;
            return -1;
        }
        return arr[head];
    }
    // ��ȡ���г���
    int size() {
        return (tail - head + MAX_SIZE) % MAX_SIZE;
    }
};






