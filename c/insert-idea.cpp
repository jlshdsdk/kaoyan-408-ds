// 直接插入排序：把待插元素插入前面已排序区
#include <iostream>
using namespace std;

void print_pass(const int a[], int n, int pass) {
    cout << "pass " << pass << ":";
    for (int i = 0; i < n; i++) cout << " " << a[i];
    cout << "\n";
}

// 直接插入排序，按趟打印
void insert_sort(int a[], int n) {
    if (n <= 0) {
        cout << "error\n";
        return;
    }
    print_pass(a, n, 0);
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
        print_pass(a, n, i);
    }
}

int main() {
    int a[] = {5, 2, 8, 1, 9, 3};
    int n = 6;
    insert_sort(a, n);
    cout << "result:";
    for (int i = 0; i < n; i++) cout << " " << a[i];
    cout << "\n";
    return 0;
}
