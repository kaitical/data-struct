#define _CRT_SECURE_NO_WARNINGS 1
#include "../../vector+complex/vector.h"
#include "../../vector+complex/complex.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>


void bubble_sort(Vector<Complex>& v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v.size() - i - 1; j++) {
            if (v[j] < v[j + 1]) {
                swap(v[j], v[j + 1]);
            }
        }
    }
}

void merge_sort(Vector<Complex>& v, int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    merge_sort(v, l, mid);
    merge_sort(v, mid + 1, r);
    Vector<Complex> tmp(r - l + 1);
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r) {
        if (v[i] < v[j]) {
            tmp[k++] = v[j++];
        }
        else {
            tmp[k++] = v[i++];
        }
    }
    while (i <= mid) {
        tmp[k++] = v[i++];
    }
    while (j <= r) {
        tmp[k++] = v[j++];
    }
    for (int i = 0; i < tmp.size(); i++) {
        v[l + i] = tmp[i];
    }
}
void bubble_sortdif(Vector<Complex>& v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v.size() - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
            }
        }
    }
}

void merge_sortdif(Vector<Complex>& v, int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    merge_sort(v, l, mid);
    merge_sort(v, mid + 1, r);
    Vector<Complex> tmp(r - l + 1);
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r) {
        if (v[i] > v[j]) {
            tmp[k++] = v[j++];
        }
        else {
            tmp[k++] = v[i++];
        }
    }
    while (i <= mid) {
        tmp[k++] = v[i++];
    }
    while (j <= r) {
        tmp[k++] = v[j++];
    }
    for (int i = 0; i < tmp.size(); i++) {
        v[l + i] = tmp[i];
    }
}
Vector<Complex> findRange(const Vector<Complex>& v, double m1, double m2) {
    Vector<Complex> res;
    for (int i = 0; i < v.size(); i++) {
        double m = v[i].getModulus();
        if (m >= m1 && m < m2) {
            res.insert(v[i]);
        }
    }
    return res;
}

int main() {//����������������飺
    srand(time(NULL));
    Vector<Complex> v(10);
    for (int i = 0; i < 10; i++) {
        v.insert(rand() % 10, Complex(rand() % 10, rand() % 10));
    }
    cout << "��ҵһ��" << endl;
    //����ǰ��
    cout << "����ǰ:" << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    //���Һ�
    v.unsort();
    cout << "���Һ�" << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    //����������4��4��
    cout << "����������4��4��,(1,4):" << endl;
    Complex c1(4, 4),c2(1,4);
   
    if (v.find(c1) == -1) {
        cout << "û�ҵ�" << c1<<endl;
    }
    else {
        cout << "�ҵ��� " << c1 << " at " << v.find(c1) << endl;
    }//ȫ���������
    if (v.find(c2) == -1) {
        cout << "û�ҵ�" <<c2<< endl;
    }
    else {
        cout << "�ҵ��� " << c2 << " at " << v.find(c2) << endl;
    }//ȫ���������

    v.insert(rand() % 10, c1);//������루4��4��
    cout << "������루4��4���� :" << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    //ɾ��������
    v.remove(rand() % 10);
    cout << "���ɾ��������:" << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    //Ψһ����
    v.deduplicate();
    cout << "Ψһ����:" << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    cout << "��ҵ����" << endl;
    Vector<Complex> v1(4000);
    for (int i = 0; i < 4000; i++) {
        v1.insert(rand() % 10, Complex(rand() % 10, rand() % 10));
    }
    Vector<Complex> v2 = v1;
    clock_t start, end;
    //��������
    start = clock();
    bubble_sort(v1);
    end = clock();
    cout << "Bubble sort����: " << end - start << "ms" << endl;

    //�鲢����
    start = clock();
    merge_sort(v2, 0, 3999);
    end = clock();
    cout << "Merge sort����: " << end - start << "ms" << endl;

    start = clock();
    bubble_sort(v1);
    end = clock();
    cout << "Bubble sort˳��: " << end - start << "ms" << endl;

    start = clock();
    merge_sort(v2, 0, 3999);
    end = clock();
    cout << "Merge sort˳��: " << end - start << "ms" << endl;

    start = clock();
    bubble_sortdif(v1);
    end = clock();
    cout << "Bubble sort����: " << end - start << "ms" << endl;

    start = clock();
    merge_sortdif(v2, 0, 3999);
    end = clock();
    cout << "Merge sort����: " << end - start << "ms" << endl;
    cout << "��ҵ����" << endl;
    cout << "���������v3���������飬������" << endl;
    Vector<Complex> v3(10);
    for (int i = 0; i < 10; i++) {
        v3.insert(rand() % 10, Complex(rand() % 10, rand() % 10));
    }
    bubble_sort(v3);
    for (int i = 0; i < v3.size(); i++) {
        cout << v3[i] << " ";
    }

    cout << endl << "���Բ���ģ��[0,4)���䣺" << endl;
    Vector<Complex>res(10);
    res = findRange(v3, 0, 4);
    for (int i = 0; i < res.size(); i++) {
        cout << res[i] << " ";
    }
}
