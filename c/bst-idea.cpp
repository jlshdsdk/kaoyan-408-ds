// 二叉搜索树：左小右大；查找演示
#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
};

Node* insert(Node* p, int key) {
    if (!p) return new Node{key, nullptr, nullptr};
    if (key < p->key) p->left = insert(p->left, key);
    else if (key > p->key) p->right = insert(p->right, key);
    // 相等则不插
    return p;
}

// 找到返回结点指针，否则 nullptr；打印比较路径
Node* search(Node* p, int key) {
    while (p) {
        cout << "visit " << p->key << "\n";
        if (key == p->key) return p;
        if (key < p->key) p = p->left;
        else p = p->right;
    }
    return nullptr;
}

void freeTree(Node* p) {
    if (!p) return;
    freeTree(p->left);
    freeTree(p->right);
    delete p;
}

int main() {
    int seq[] = {8, 3, 10, 1, 6, 14, 4};
    Node* root = nullptr;
    for (int x : seq) root = insert(root, x);

    cout << "search 6\n";
    if (search(root, 6)) cout << "found\n";
    else cout << "not found\n";

    cout << "search 7\n";
    if (search(root, 7)) cout << "found\n";
    else cout << "not found\n";

    freeTree(root);
    return 0;
}
