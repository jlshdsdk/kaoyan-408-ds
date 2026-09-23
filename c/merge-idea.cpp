// 归并排序思路：先两两归并，再扩大归并段
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

// 自底向上：先长度为 1 的两两归并
void mergeSortBottomUp(int a[], int n) {
    int* tmp = new int[n];
    for (int width = 1; width < n; width *= 2) {
        for (int i = 0; i < n; i += 2 * width) {
            int mid = i + width - 1;
            int right = i + 2 * width - 1;
            if (mid >= n - 1) break;
            if (right >= n) right = n - 1;
            merge(a, i, mid, right, tmp);
        }
        printArr(a, n);
    }
    delete[] tmp;
}

int main() {
    int a[] = {5, 2, 8, 1, 9, 3};
    int n = 6;
    printArr(a, n);
    mergeSortBottomUp(a, n);
    return 0;
}
