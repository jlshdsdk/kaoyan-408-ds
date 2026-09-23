// 冒泡排序及其改进：某趟无交换则提前结束
#include <iostream>
using namespace std;

void print_arr(const int a[], int n) {
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << a[i];
    }
    cout << "\n";
}

void bubble_sort(int a[], int n) {
    if (n <= 0) {
        cout << "error\n";
        return;
    }
    cout << "init: ";
    print_arr(a, n);
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
                swapped = true;
            }
        }
        cout << "pass " << (i + 1) << ": ";
        print_arr(a, n);
        if (!swapped) {
            cout << "early stop at pass " << (i + 1) << "\n";
            return;
        }
        cout << "swapped=1, continue\n";
    }
}

int main() {
    int a[] = {5, 2, 8, 1, 9, 3};
    int n = 6;
    bubble_sort(a, n);
    cout << "result: ";
    print_arr(a, n);
    return 0;
}
