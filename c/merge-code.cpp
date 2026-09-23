// 归并排序代码（递归）：打印每一层归并结果
#include <iostream>
using namespace std;

void printArr(const int a[], int n) {
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << a[i];
    }
    cout << "\n";
}

void merge(int a[], int L, int M, int R, int tmp[]) {
    int i = L, j = M + 1, k = L;
    while (i <= M && j <= R) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else tmp[k++] = a[j++];
    }
    while (i <= M) tmp[k++] = a[i++];
    while (j <= R) tmp[k++] = a[j++];
    for (int t = L; t <= R; t++) a[t] = tmp[t];
}

void mergeSort(int a[], int L, int R, int tmp[], int n) {
    if (L >= R) return;
    int M = L + (R - L) / 2;
    mergeSort(a, L, M, tmp, n);
    mergeSort(a, M + 1, R, tmp, n);
    merge(a, L, M, R, tmp);
    printArr(a, n);  // 每次归并后打印整表
}

int main() {
    int a[] = {5, 2, 8, 1, 9, 3};
    int n = 6;
    int tmp[6];
    printArr(a, n);
    mergeSort(a, 0, n - 1, tmp, n);
    return 0;
}
