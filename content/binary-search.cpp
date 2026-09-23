// 折半查找：有序表上比较，打印 low mid high
#include <iostream>
using namespace std;

// 返回下标；找不到返回 -1。过程打印 low/mid/high
int binarySearch(const int a[], int n, int key) {
    if (n <= 0) return -1;
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        cout << "low=" << low << " mid=" << mid << " high=" << high
             << " a[mid]=" << a[mid] << "\n";
        if (a[mid] == key) return mid;
        if (a[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int main() {
    int a[] = {2, 5, 8, 12, 16, 23, 38};
    int n = 7;

    cout << "search 16\n";
    int p = binarySearch(a, n, 16);
    if (p >= 0) cout << "found index=" << p << "\n";
    else cout << "error\n";

    cout << "search 7\n";
    p = binarySearch(a, n, 7);
    if (p >= 0) cout << "found index=" << p << "\n";
    else cout << "not found\n";

    // 空表
    p = binarySearch(a, 0, 1);
    if (p < 0) cout << "empty=-1\n";
    return 0;
}
