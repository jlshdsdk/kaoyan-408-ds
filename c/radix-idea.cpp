// 基数排序思路：LSD，先按个位再按十位分配收集
#include <iostream>
using namespace std;

void printArr(const int a[], int n) {
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << a[i];
    }
    cout << "\n";
}

// 按某十进制位（exp=1 个位，exp=10 十位）分配到 10 个桶再收集
void countPass(int a[], int n, int exp) {
    int bucket[10][8];
    int cnt[10] = {0};
    for (int i = 0; i < n; i++) {
        int d = (a[i] / exp) % 10;
        bucket[d][cnt[d]++] = a[i];
    }
    int k = 0;
    for (int d = 0; d < 10; d++) {
        for (int j = 0; j < cnt[d]; j++) a[k++] = bucket[d][j];
    }
}

void radixSort(int a[], int n) {
    countPass(a, n, 1);   // 个位
    printArr(a, n);
    countPass(a, n, 10);  // 十位
    printArr(a, n);
}

int main() {
    int a[] = {21, 15, 8, 32, 4, 27};
    int n = 6;
    printArr(a, n);
    radixSort(a, n);
    return 0;
}
