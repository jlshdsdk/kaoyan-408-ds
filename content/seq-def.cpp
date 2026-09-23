// 顺序表：定义、创建、按下标访问、按值查找
#include <iostream>
using namespace std;

const int MAXN = 64;

struct SeqList {
    int data[MAXN];
    int length;
};

void init(SeqList& L) {
    L.length = 0;
}

// 用给定数组创建顺序表
bool create(SeqList& L, const int a[], int n) {
    if (n < 0 || n > MAXN) {
        cout << "error\n";
        return false;
    }
    for (int i = 0; i < n; i++) L.data[i] = a[i];
    L.length = n;
    return true;
}

// 按下标访问，合法下标返回 true
bool get(const SeqList& L, int i, int& out) {
    if (i < 0 || i >= L.length) {
        cout << "error\n";
        return false;
    }
    out = L.data[i];
    return true;
}

// 按值查找，返回首次出现的下标；找不到返回 -1
int find(const SeqList& L, int x) {
    for (int i = 0; i < L.length; i++) {
        if (L.data[i] == x) return i;
    }
    return -1;
}

void print(const SeqList& L) {
    cout << "[";
    for (int i = 0; i < L.length; i++) {
        if (i) cout << ",";
        cout << L.data[i];
    }
    cout << "]\n";
}

int main() {
    SeqList L;
    init(L);
    int a[] = {12, 7, 9, 4};
    create(L, a, 4);
    print(L);

    int v = 0;
    // 按下标访问：看下标 2
    if (get(L, 2, v)) cout << "get(2)=" << v << "\n";

    // 按值查找 9
    int pos = find(L, 9);
    if (pos >= 0) cout << "find(9)=" << pos << "\n";
    else cout << "error\n";

    // 空表与找不到
    SeqList E;
    init(E);
    if (!get(E, 0, v)) { /* empty */ }
    if (find(L, 99) < 0) cout << "find(99)=-1\n";
    return 0;
}
