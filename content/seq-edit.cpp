// 顺序表：插入、删除
#include <iostream>
using namespace std;

const int MAXN = 64;

struct SeqList {
    int data[MAXN];
    int length;
};

void init(SeqList& L) { L.length = 0; }

bool create(SeqList& L, const int a[], int n) {
    if (n < 0 || n > MAXN) {
        cout << "error\n";
        return false;
    }
    for (int i = 0; i < n; i++) L.data[i] = a[i];
    L.length = n;
    return true;
}

// 在下标 i 处插入 x（0<=i<=length）
bool insertAt(SeqList& L, int i, int x) {
    if (i < 0 || i > L.length || L.length >= MAXN) {
        cout << "error\n";
        return false;
    }
    for (int j = L.length; j > i; j--) L.data[j] = L.data[j - 1];
    L.data[i] = x;
    L.length++;
    return true;
}

// 删除下标 i 处元素
bool eraseAt(SeqList& L, int i) {
    if (i < 0 || i >= L.length) {
        cout << "error\n";
        return false;
    }
    for (int j = i; j < L.length - 1; j++) L.data[j] = L.data[j + 1];
    L.length--;
    return true;
}

// 按值删除首次出现的 x
bool eraseValue(SeqList& L, int x) {
    int i = -1;
    for (int k = 0; k < L.length; k++) {
        if (L.data[k] == x) {
            i = k;
            break;
        }
    }
    if (i < 0) {
        cout << "error\n";
        return false;
    }
    return eraseAt(L, i);
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

    // 在下标 1 插入 5 -> [12,5,7,9,4]
    if (insertAt(L, 1, 5)) {
        cout << "insert 5 at 1: ";
        print(L);
    }

    // 删除值 9 -> [12,5,7,4]
    if (eraseValue(L, 9)) {
        cout << "erase 9: ";
        print(L);
    }

    // 越界与空删
    if (!insertAt(L, 99, 1)) { /* error */ }
    SeqList E;
    init(E);
    if (!eraseValue(E, 1)) { /* empty */ }
    return 0;
}
