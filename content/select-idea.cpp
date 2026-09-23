// 简单选择排序思路：每趟选最小元换到前面
#include <iostream>
using namespace std;

void printArr(const int a[], int n) {
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << a[i];
    }
    cout << "\n";
}

void selectSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int k = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[k]) k = j;
        }
        if (k != i) {
            int t = a[i];
            a[i] = a[k];
            a[k] = t;
        }
    }
}

int main() {
    int a[] = {5, 2, 8, 1, 9, 3};
    int n = 6;
    printArr(a, n);
    selectSort(a, n);
    printArr(a, n);
    return 0;
}
