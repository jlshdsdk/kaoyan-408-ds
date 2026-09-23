// 折半插入排序代码：每趟打印 low high mid
#include <iostream>
using namespace std;

void print_arr(const int a[], int n) {
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << a[i];
    }
    cout << "\n";
}

void bin_insert_sort(int a[], int n) {
    if (n <= 0) {
        cout << "error\n";
        return;
    }
    cout << "init: ";
    print_arr(a, n);
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int low = 0, high = i - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            cout << "pass " << i << " low=" << low << " high=" << high
                 << " mid=" << mid << "\n";
            if (a[mid] > key) high = mid - 1;
            else low = mid + 1;
        }
        for (int j = i - 1; j >= low; j--) a[j + 1] = a[j];
        a[low] = key;
        cout << "after pass " << i << ": ";
        print_arr(a, n);
    }
}

int main() {
    int a[] = {5, 2, 8, 1, 9, 3};
    int n = 6;
    bin_insert_sort(a, n);
    cout << "result: ";
    print_arr(a, n);
    return 0;
}
