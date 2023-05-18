#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <chrono> // 用于计时
#include <algorithm> // 用于反转数组

using namespace std;
using namespace std::chrono;

// 起泡排序
template<typename T>
void bubbleSort(vector<T>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 插入排序
template<typename T>
void insertionSort(vector<T>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int j = i - 1;
        T key = arr[i];
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// 选择排序
template<typename T>
void selectionSort(vector<T>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(arr[i], arr[min_idx]);
        }
    }
}

// 归并排序
template<typename T>
void merge(vector<T>& arr, int left, int mid, int right) {
    vector<T> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        if (arr[i] < arr[j]) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (k = 0, i = left; i <= right; ++i, ++k) {
        arr[i] = temp[k];
    }
}

template<typename T>
void mergeSort(vector<T>& arr, int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// 快速排序
template<typename T>
int partition(vector<T>& arr, int left, int right) {
    T pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);
    return i + 1;
}

template<typename T>
void quickSort(vector<T>& arr, int left, int right) {
    if (left >= right) return;
    int pivot_idx = partition(arr, left, right);
    quickSort(arr, left, pivot_idx - 1);
    quickSort(arr, pivot_idx + 1, right);
}

int main() {
    // 生成测试用的顺序、逆序和随机序列
    vector<int> arr1(1000), arr4(1000), arr5(1000), arr6(1000), arr7(1000), arr8(1000), arr9(1000), arr10(1000), arr11(1000), arr12(1000), arr13(1000), arr14(1000), arr15(1000);
    for (int i = 0; i < 1000; ++i) {
        arr1[i] = i;
    }
    for (int i = 0; i < 1000; ++i) {
        arr4[i] = i;
    }
    for (int i = 0; i < 1000; ++i) {
        arr7[i] = i;
    }
    for (int i = 0; i < 1000; ++i) {
        arr10[i] = i;
    }
    for (int i = 0; i < 1000; ++i) {
        arr13[i] = i;
    }
    vector<int> arr2(1000);
    for (int i = 0; i < 1000; ++i) {
        arr2[i] = 999 - i;
    }
    for (int i = 0; i < 1000; ++i) {
        arr5[i] = 999 - i;
    }
    for (int i = 0; i < 1000; ++i) {
        arr8[i] = 999 - i;
    }
    for (int i = 0; i < 1000; ++i) {
        arr11[i] = 999 - i;
    }
    for (int i = 0; i < 1000; ++i) {
        arr14[i] = 999 - i;
    }
    vector<int> arr3(1000);
    for (int i = 0; i < 1000; ++i) {
        arr3[i] = rand();
    }
    for (int i = 0; i < 1000; ++i) {
        arr6[i] = rand();
    }
    for (int i = 0; i < 1000; ++i) {
        arr9[i] = rand();
    }
    for (int i = 0; i < 1000; ++i) {
        arr12[i] = rand();
    }
    for (int i = 0; i < 1000; ++i) {
        arr15[i] = rand();
    }
    // 对三种序列分别使用五种排序算法进行测试，并输出执行时间
    cout << "---- 顺序序列 ----" << endl;

    auto start = high_resolution_clock::now(); // 计时开始

    bubbleSort(arr1);

    auto stop = high_resolution_clock::now(); // 计时结束

    auto duration = duration_cast<microseconds>(stop - start); // 计算执行时间

    cout << "起泡排序的执行时间为：" << duration.count() << " 微秒" << endl;
    start = high_resolution_clock::now();

    insertionSort(arr4);

    stop = high_resolution_clock::now();

    duration = duration_cast<microseconds>(stop - start);

    cout << "插入排序的执行时间为：" << duration.count() << " 微秒" << endl;
    start = high_resolution_clock::now();

    selectionSort(arr7);

    stop = high_resolution_clock::now();

    duration = duration_cast<microseconds>(stop - start);

    cout << "选择排序的执行时间为：" << duration.count() << " 微秒" << endl;
    start = high_resolution_clock::now();

    mergeSort(arr10, 0, arr1.size() - 1);

    stop = high_resolution_clock::now();

    duration = duration_cast<microseconds>(stop - start);

    cout << "归并排序的执行时间为：" << duration.count() << " 微秒" << endl;
    start = high_resolution_clock::now();

    quickSort(arr13, 0, arr13.size() - 1);

    stop = high_resolution_clock::now();

    duration = duration_cast<microseconds>(stop - start);

    cout << "快速排序的执行时间为：" << duration.count() << " 微秒" << endl;

    cout << endl;

    cout << "---- 逆序序列 ----" << endl;

    start = high_resolution_clock::now();

    bubbleSort(arr2);

    stop = high_resolution_clock::now();

    duration = duration_cast<microseconds>(stop - start);

    cout << "起泡排序的执行时间为：" << duration.count() << " 微秒" << endl;
    start = high_resolution_clock::now();

    insertionSort(arr5);

    stop = high_resolution_clock::now();

    duration = duration_cast<microseconds>(stop - start);

    cout << "插入排序的执行时间为：" << duration.count() << " 微秒" << endl;
    start = high_resolution_clock::now();

    selectionSort(arr8);

    stop = high_resolution_clock::now();

    duration = duration_cast<microseconds>(stop - start);

    cout << "选择排序的执行时间为：" << duration.count() << " 微秒" << endl;
    start = high_resolution_clock::now();

    mergeSort(arr11, 0, arr11.size() - 1);

    stop = high_resolution_clock::now();

    duration = duration_cast<microseconds>(stop - start);

    cout << "归并排序的执行时间为：" << duration.count() << " 微秒" << endl;
    start = high_resolution_clock::now();

    quickSort(arr14, 0, arr14.size() - 1);

    stop = high_resolution_clock::now();

    duration = duration_cast<microseconds>(stop - start);

    cout << "快速排序的执行时间为：" << duration.count() << " 微秒" << endl;


    cout << endl;

    cout << "---- 随机序列 ----" << endl;

    start = high_resolution_clock::now();

    bubbleSort(arr3);

    stop = high_resolution_clock::now();

    duration = duration_cast<microseconds>(stop - start);

    cout << "起泡排序的执行时间为：" << duration.count() << " 微秒" << endl;

    start = high_resolution_clock::now();

    insertionSort(arr6);

    stop = high_resolution_clock::now();

    duration = duration_cast<microseconds>(stop - start);

    cout << "插入排序的执行时间为：" << duration.count() << " 微秒" << endl;
    start = high_resolution_clock::now();

    selectionSort(arr9);

    stop = high_resolution_clock::now();

    duration = duration_cast<microseconds>(stop - start);

    cout << "选择排序的执行时间为：" << duration.count() << " 微秒" << endl;
    start = high_resolution_clock::now();

    mergeSort(arr12, 0, arr12.size() - 1);

    stop = high_resolution_clock::now();

    duration = duration_cast<microseconds>(stop - start);

    cout << "归并排序的执行时间为：" << duration.count() << " 微秒" << endl;

    start = high_resolution_clock::now();

    quickSort(arr15, 0, arr15.size() - 1);

    stop = high_resolution_clock::now();

    duration = duration_cast<microseconds>(stop - start);

    cout << "快速排序的执行时间为：" << duration.count() << " 微秒" << endl;
    return 0;
}
