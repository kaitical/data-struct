#pragma once
#include <iostream>
#define MAX_SIZE 10  // 队列最大长度

class Queue {
private:
    int head;  // 头指针，初始时为0
    int tail;  // 尾指针，初始时为0
    int arr[MAX_SIZE];  // 用数组存储队列元素
public:
    Queue() {  // 构造函数
        head = tail = 0;
    }
    // 判断队列是否为空
    bool is_empty() {
        return head == tail;
    }
    // 判断队列是否已满
    bool is_full() {
        return (tail + 1) % MAX_SIZE == head;
    }
    // 元素入队列
    bool enqueue(int x) {
        if (is_full()) {
            std::cout << "Queue is full, cannot enqueue element." << std::endl;
            return false;
        }
        arr[tail] = x;
        tail = (tail + 1) % MAX_SIZE;  // 对尾指针进行取模，确保新元素加入在最后
        return true;
    }
    // 元素出队列
    bool dequeue() {
        if (is_empty()) {
            std::cout << "Queue is empty, cannot dequeue element." << std::endl;
            return false;
        }
        head = (head + 1) % MAX_SIZE;  // 头指针移动到队列下一个元素
        return true;
    }
    // 获取队头元素
    int front() {
        if (is_empty()) {
            std::cout << "Queue is empty, no front element." << std::endl;
            return -1;
        }
        return arr[head];
    }
    // 获取队列长度
    int size() {
        return (tail - head + MAX_SIZE) % MAX_SIZE;
    }
};






