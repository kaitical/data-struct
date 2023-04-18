#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include "../../stack/stack.h"
#include "../../vector+complex/vector.h"
#include<time.h>

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
	srand(time(0)); 
	cout<<"text1:"<<endl;
    int n,x;
    int ex1[6],ex2[2];
    ex1[0]=2;ex1[1]=1;ex1[2]=5;ex1[3]=6;ex1[4]=2;ex1[5]=3;
	ex2[0]=2;ex2[1]=4;
	Vector<int>height1(ex1,0,6);
	Vector<int>height2(ex2,0,2);
	cout<<"the maxarea in example1 [2,1,5,6,2,3] is:"<< largestRectangleArea(height1)<<endl;
	cout<<"the maxarea in example2 [2,4] is:"<< largestRectangleArea(height2)<<endl;
    
	cout<<"text2:"<<endl;
    for (int k = 1; k <= 10; k++) {
        Vector<int> heights;
        int n = rand() % 105;
        for (int i = 0; i < n; i++) {
            heights.insert(rand() % 104);
        }
        int area = largestRectangleArea(heights);
        cout << "the number" << k << "'s maxarea is " << area << endl;
    }
    cout<<"enter the number of your posts:"<<endl;
    cin>>x;
    int a[x];
    cout<<"enter their heights:"<<endl;
    for(int i=0;i<x;i++){
    	cin>>a[i];
	}
	Vector<int>height(a,0,x);
	cout<<"your posts' maxarea is "<< largestRectangleArea(height)<<endl;
    return 0;
}
