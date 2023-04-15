#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include "../../stack/stack.h"
#include "../../vector+complex/vector.h"

using namespace std;

int largestRectangleArea(Vector<int>& heights) {
    int n = heights.size();
    Vector<int> left(n), right(n);
    Stack<int> stk;

    // 计算每个柱子左边最近的小于它的柱子
    for (int i = 0; i < n; i++) {
        while (!stk.isEmpty() && heights[stk.gettop()] >= heights[i]) {
            stk.pop();
        }
        left[i] = stk.isEmpty() ? -1 : stk.gettop();
        stk.push(i);
    }

    // 清空栈
    while (!stk.isEmpty()) {
        stk.pop();
    }

    // 计算每个柱子右边最近的小于它的柱子
    for (int i = n - 1; i >= 0; i--) {
        while (!stk.isEmpty() && heights[stk.gettop()] >= heights[i]) {
            stk.pop();
        }
        right[i] = stk.isEmpty() ? n : stk.gettop();
        stk.push(i);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int area = (right[i] - left[i] - 1) * heights[i];
        ans = max(ans, area);
    }

    return ans;
}

int main() {
    int n;
    for (int k = 1; k <= 10; k++) {
        Vector<int> heights;
        int n = rand() % 105;
        for (int i = 0; i < n; i++) {
            heights.insert(rand() % 104);
        }
        int area = largestRectangleArea(heights);
        cout << "the number" << k << "'s maxarea is " << area << endl;
    }
    return 0;
}
