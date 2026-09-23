// 用上下界判断是否为二叉搜索树
#include <iostream>
#include <climits>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
};

Node* make(int key, Node* l = nullptr, Node* r = nullptr) {
    return new Node{key, l, r};
}

// 合法区间 (lo, hi)，开区间；空树为真
bool isBST(Node* p, long long lo, long long hi) {
    if (!p) return true;
    if (p->key <= lo || p->key >= hi) return false;
    return isBST(p->left, lo, p->key) && isBST(p->right, p->key, hi);
}

bool check(Node* root) {
    return isBST(root, LLONG_MIN, LLONG_MAX);
}

void freeTree(Node* p) {
    if (!p) return;
    freeTree(p->left);
    freeTree(p->right);
    delete p;
}

int main() {
    // 真 BST：与前面同一插入序列形成的树
    Node* good = make(8,
        make(3, make(1), make(6, make(4), nullptr)),
        make(10, nullptr, make(14)));
    cout << "good=" << (check(good) ? "true" : "false") << "\n";

    // 假树：根 5，左 1，右 4（4 在右却小于根）
    Node* bad = make(5, make(1), make(4));
    cout << "bad=" << (check(bad) ? "true" : "false") << "\n";

    // 仅查父子会漏的经典反例：右子树里藏了更小的 4
    Node* tricky = make(5, make(1), make(6, make(4), nullptr));
    cout << "tricky=" << (check(tricky) ? "true" : "false") << "\n";

    // 空树
    cout << "empty=" << (check(nullptr) ? "true" : "false") << "\n";

    freeTree(good);
    freeTree(bad);
    freeTree(tricky);
    return 0;
}
