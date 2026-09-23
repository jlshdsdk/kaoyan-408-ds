// 直接插入排序代码（不带哨兵），打印每趟
#include <iostream>
using namespace std;

void print_arr(const int a[], int n) {
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << a[i];
    }
    cout << "\n";
}

void insert_sort(int a[], int n) {
    if (n <= 0) {
        cout << "error\n";
        return;
    }
    cout << "init: ";
    print_arr(a, n);
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
        cout << "pass " << i << ": ";
        print_arr(a, n);
    }
}

int main() {
    int a[] = {5, 2, 8, 1, 9, 3};
    int n = 6;
    insert_sort(a, n);
    cout << "result: ";
    print_arr(a, n);
    return 0;
}
