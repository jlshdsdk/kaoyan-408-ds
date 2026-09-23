// 折半插入排序：用折半找插入位置，比较可减半，移动不变
#include <iostream>
using namespace std;

void print_pass(const int a[], int n, int pass) {
    cout << "pass " << pass << ":";
    for (int i = 0; i < n; i++) cout << " " << a[i];
    cout << "\n";
}

void bin_insert_sort(int a[], int n) {
    if (n <= 0) {
        cout << "error\n";
        return;
    }
    print_pass(a, n, 0);
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int low = 0, high = i - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            cout << "  i=" << i << " low=" << low << " high=" << high
                 << " mid=" << mid << "\n";
            if (a[mid] > key) high = mid - 1;
            else low = mid + 1;
        }
        for (int j = i - 1; j >= low; j--) a[j + 1] = a[j];
        a[low] = key;
        print_pass(a, n, i);
    }
}

int main() {
    int a[] = {5, 2, 8, 1, 9, 3};
    int n = 6;
    bin_insert_sort(a, n);
    cout << "result:";
    for (int i = 0; i < n; i++) cout << " " << a[i];
    cout << "\n";
    return 0;
}
