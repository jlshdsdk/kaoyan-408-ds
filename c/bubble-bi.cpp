// 双向冒泡排序：一趟先左到右再右到左
#include <iostream>
using namespace std;

void print_arr(const int a[], int n) {
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << a[i];
    }
    cout << "\n";
}

void bubble_bi_sort(int a[], int n) {
    if (n <= 0) {
        cout << "error\n";
        return;
    }
    cout << "init: ";
    print_arr(a, n);
    int left = 0, right = n - 1;
    int pass = 0;
    while (left < right) {
        pass++;
        for (int i = left; i < right; i++) {
            if (a[i] > a[i + 1]) {
                int t = a[i];
                a[i] = a[i + 1];
                a[i + 1] = t;
            }
        }
        right--;
        cout << "pass " << pass << " L->R: ";
        print_arr(a, n);

        for (int i = right; i > left; i--) {
            if (a[i - 1] > a[i]) {
                int t = a[i - 1];
                a[i - 1] = a[i];
                a[i] = t;
            }
        }
        left++;
        cout << "pass " << pass << " R->L: ";
        print_arr(a, n);
    }
}

int main() {
    int a[] = {5, 2, 8, 1, 9, 3};
    int n = 6;
    bubble_bi_sort(a, n);
    cout << "result: ";
    print_arr(a, n);
    return 0;
}
