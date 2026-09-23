// 堆排序代码：建大根堆后打印每次取顶
#include <iostream>
using namespace std;

void printArr(const int a[], int n) {
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << a[i];
    }
    cout << "\n";
}

void siftDown(int a[], int i, int n) {
    while (true) {
        int l = 2 * i + 1, r = 2 * i + 2, largest = i;
        if (l < n && a[l] > a[largest]) largest = l;
        if (r < n && a[r] > a[largest]) largest = r;
        if (largest == i) break;
        int t = a[i];
        a[i] = a[largest];
        a[largest] = t;
        i = largest;
    }
}

void heapSort(int a[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) siftDown(a, i, n);
    cout << "heap: ";
    printArr(a, n);
    for (int end = n - 1; end > 0; end--) {
        int t = a[0];
        a[0] = a[end];
        a[end] = t;
        siftDown(a, 0, end);
        cout << "take: ";
        printArr(a, n);
    }
}

int main() {
    int a[] = {5, 2, 8, 1, 9, 3};
    int n = 6;
    cout << "init: ";
    printArr(a, n);
    heapSort(a, n);
    return 0;
}
