// 二叉树与完全二叉树 - 定义与性质（满的完全二叉树 1..7）
#include <iostream>
using namespace std;

static const int N = 7;

int parent(int i) { return i / 2; }
int left(int i) { return 2 * i; }
int right(int i) { return 2 * i + 1; }

bool is_leaf(int i, int n) {
    return left(i) > n;
}

int main() {
    // 1-based heap-like layout for complete binary tree 1..7
    int a[N + 1];
    for (int i = 1; i <= N; i++) a[i] = i;

    cout << "tree=";
    for (int i = 1; i <= N; i++) cout << a[i];
    cout << "\n";

    for (int i = 1; i <= N; i++) {
        cout << "i=" << i;
        if (i > 1) cout << " parent=" << parent(i);
        if (left(i) <= N) cout << " L=" << left(i);
        if (right(i) <= N) cout << " R=" << right(i);
        if (is_leaf(i, N)) cout << " leaf";
        cout << "\n";
    }

    // leaves of complete tree of n nodes sit on last two levels
    cout << "leaves=";
    for (int i = 1; i <= N; i++) {
        if (is_leaf(i, N)) cout << a[i];
    }
    cout << "\n";

    // property: at most 2^k nodes on level k (root level 0)
    cout << "level0=1 level1=2 level2=4 max\n";
    // n nodes -> height floor(log2 n)
    cout << "height=" << 2 << " for n=" << N << "\n";
    return 0;
}
