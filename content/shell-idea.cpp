// 希尔排序：增量 3 再 1（n=6），组内插入
#include <iostream>
using namespace std;

void print_arr(const int a[], int n, const char* tag) {
    cout << tag;
    for (int i = 0; i < n; i++) cout << " " << a[i];
    cout << "\n";
}

void shell_sort(int a[], int n) {
    if (n <= 0) {
        cout << "error\n";
        return;
    }
    print_arr(a, n, "init:");
    // n=6 时增量序列固定为 3,1
    int gaps[] = {3, 1};
    for (int g = 0; g < 2; g++) {
        int gap = gaps[g];
        cout << "gap=" << gap << "\n";
        for (int i = gap; i < n; i++) {
            int key = a[i];
            int j = i - gap;
            cout << "  cmp idx " << j << " and " << i << "\n";
            while (j >= 0 && a[j] > key) {
                a[j + gap] = a[j];
                j -= gap;
            }
            a[j + gap] = key;
        }
        print_arr(a, n, "after:");
    }
}

int main() {
    int a[] = {5, 2, 8, 1, 9, 3};
    int n = 6;
    shell_sort(a, n);
    print_arr(a, n, "result:");
    return 0;
}
