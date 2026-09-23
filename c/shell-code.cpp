// 希尔排序代码：gap 从 n/2 起，打印每趟
#include <iostream>
using namespace std;

void print_arr(const int a[], int n) {
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << a[i];
    }
    cout << "\n";
}

void shell_sort(int a[], int n) {
    if (n <= 0) {
        cout << "error\n";
        return;
    }
    cout << "init: ";
    print_arr(a, n);
    for (int gap = n / 2; gap >= 1; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int key = a[i];
            int j = i - gap;
            while (j >= 0 && a[j] > key) {
                a[j + gap] = a[j];
                j -= gap;
            }
            a[j + gap] = key;
        }
        cout << "gap=" << gap << ": ";
        print_arr(a, n);
    }
}

int main() {
    int a[] = {5, 2, 8, 1, 9, 3};
    int n = 6;
    shell_sort(a, n);
    cout << "result: ";
    print_arr(a, n);
    return 0;
}
