// 快速排序：左端为枢轴，每次划分后打印数组
#include <iostream>
using namespace std;

void printArr(const int a[], int n) {
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << a[i];
    }
    cout << "\n";
}

// 挖坑法：选 a[low] 为枢轴，返回枢轴最终下标
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

void quickSort(int a[], int low, int high, int n) {
    if (low >= high) return;
    int p = partition(a, low, high);
    printArr(a, n);  // 每次划分后打印
    quickSort(a, low, p - 1, n);
    quickSort(a, p + 1, high, n);
}

int main() {
    int a[] = {5, 2, 8, 1, 9, 3};
    int n = 6;
    printArr(a, n);
    quickSort(a, 0, n - 1, n);
    return 0;
}
