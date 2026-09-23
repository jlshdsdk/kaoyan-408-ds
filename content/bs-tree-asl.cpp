// 折半查找判定树：构造并算成功 ASL
#include <iostream>
using namespace std;

struct Node {
    int key;
    int depth;  // 从 1 起
    Node* left;
    Node* right;
};

Node* buildDecision(const int a[], int low, int high, int depth) {
    if (low > high) return nullptr;
    int mid = low + (high - low) / 2;
    Node* p = new Node{a[mid], depth, nullptr, nullptr};
    p->left = buildDecision(a, low, mid - 1, depth + 1);
    p->right = buildDecision(a, mid + 1, high, depth + 1);
    return p;
}

void freeTree(Node* p) {
    if (!p) return;
    freeTree(p->left);
    freeTree(p->right);
    delete p;
}

// 累加成功查找的深度之和与结点数
void sumDepth(Node* p, int& sum, int& cnt) {
    if (!p) return;
    sum += p->depth;
    cnt++;
    sumDepth(p->left, sum, cnt);
    sumDepth(p->right, sum, cnt);
}

void printInorder(Node* p) {
    if (!p) return;
    printInorder(p->left);
    cout << p->key << "(d=" << p->depth << ") ";
    printInorder(p->right);
}

int main() {
    int a[] = {2, 5, 8, 12, 16, 23, 38};
    int n = 7;
    Node* root = buildDecision(a, 0, n - 1, 1);

    cout << "inorder with depth: ";
    printInorder(root);
    cout << "\n";

    int sum = 0, cnt = 0;
    sumDepth(root, sum, cnt);
    // ASL_success = (1 + 2*2 + 4*3) / 7 = 17/7
    cout << "sum_depth=" << sum << " n=" << cnt << "\n";
    cout << "ASL_success=" << (double)sum / cnt << "\n";

    freeTree(root);

    // 空表
    Node* empty = buildDecision(a, 0, -1, 1);
    if (!empty) cout << "empty tree\n";
    return 0;
}
