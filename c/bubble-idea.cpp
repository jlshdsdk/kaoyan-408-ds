// 冒泡排序：一趟把当前最大沉到末尾
#include <iostream>
using namespace std;

void print_pass(const int a[], int n, int pass) {
    cout << "pass " << pass << ":";
    for (int i = 0; i < n; i++) cout << " " << a[i];
    cout << "\n";
}

void bubble_sort(int a[], int n) {
    if (n <= 0) {
        cout << "error\n";
        return;
    }
    print_pass(a, n, 0);
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
        print_pass(a, n, i + 1);
    }
}

int main() {
    int a[] = {5, 2, 8, 1, 9, 3};
    int n = 6;
    bubble_sort(a, n);
    cout << "result:";
    for (int i = 0; i < n; i++) cout << " " << a[i];
    cout << "\n";
    return 0;
}
