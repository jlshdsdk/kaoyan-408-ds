// 顺序查找与平均查找长度 ASL；含哨兵写法
#include <iostream>
using namespace std;

const int MAXN = 64;

// 普通顺序查找：从左到右，返回下标；找不到返回 -1
int seqSearch(const int a[], int n, int key, int& cmp) {
    cmp = 0;
    if (n <= 0) return -1;
    for (int i = 0; i < n; i++) {
        cmp++;
        if (a[i] == key) return i;
    }
    return -1;
}

// 哨兵顺序查找：a[0] 作哨兵，元素在 a[1..n]
int seqSearchSentinel(int a[], int n, int key, int& cmp) {
    cmp = 0;
    if (n < 0) return 0;
    a[0] = key;
    int i = n;
    while (a[i] != key) {
        cmp++;
        i--;
    }
    // 最后一次相等比较也算一次
    cmp++;
    return i;  // i==0 表示失败
}

// 等概率成功 ASL = (1+2+...+n)/n
double aslSuccess(int n) {
    if (n <= 0) return 0;
    int sum = 0;
    for (int i = 1; i <= n; i++) sum += i;
    return (double)sum / n;
}

int main() {
    // 演示表：下标 0..5 对应 4 7 2 9 1 6
    int a[] = {4, 7, 2, 9, 1, 6};
    int n = 6;

    int cmp = 0;
    int p = seqSearch(a, n, 9, cmp);
    cout << "search(9) index=" << p << " cmp=" << cmp << "\n";

    p = seqSearch(a, n, 5, cmp);
    cout << "search(5) index=" << p << " cmp=" << cmp << "\n";

    // 哨兵：a0[1..6] 存表，a0[0] 作哨兵
    int a0[MAXN] = {0, 4, 7, 2, 9, 1, 6};
    p = seqSearchSentinel(a0, n, 9, cmp);
    cout << "sentinel(9) index=" << p << " cmp=" << cmp << "\n";
    p = seqSearchSentinel(a0, n, 5, cmp);
    cout << "sentinel(5) index=" << p << " cmp=" << cmp << "\n";

    cout << "ASL_success=" << aslSuccess(n) << "\n";
    // 等概率失败：无序表失败总要扫完，比较 n 次；失败 ASL = n
    cout << "ASL_fail_cmp=" << n << "\n";

    // 空表
    cmp = 0;
    p = seqSearch(a, 0, 1, cmp);
    if (p < 0) cout << "empty=-1\n";
    return 0;
}
