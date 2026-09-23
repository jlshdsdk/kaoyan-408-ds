// 快速排序：最左为枢轴，一次划分后再递归
#include <iostream>
using namespace std;

void print_arr(const int a[], int n, const char* tag) {
    cout << tag;
    for (int i = 0; i < n; i++) cout << " " << a[i];
    cout << "\n";
}

int partition(int a[], int low, int high) {
    int pivot = a[low];
    while (low < high) {
        while (low < high && a[high] >= pivot) high--;
        a[low] = a[high];
        while (low < high && a[low] <= pivot) low++;
        a[high] = a[low];
    }
    a[low] = pivot;
    return low;
}

void quick_sort(int a[], int low, int high, int n) {
    if (low >= high) return;
    int p = partition(a, low, high);
    cout << "pivot@" << p << " after partition:";
    for (int i = 0; i < n; i++) cout << " " << a[i];
    cout << "\n";
    quick_sort(a, low, p - 1, n);
    quick_sort(a, p + 1, high, n);
}

int main() {
    int a[] = {5, 2, 8, 1, 9, 3};
    int n = 6;
    print_arr(a, n, "init:");
    cout << "pivot=a[0]=5\n";
    quick_sort(a, 0, n - 1, n);
    print_arr(a, n, "result:");
    return 0;
}
