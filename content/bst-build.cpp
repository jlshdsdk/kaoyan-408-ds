// 二叉搜索树：查找、插入、构建；打印中序
#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
};

Node* insert(Node* p, int key) {
    if (!p) {
        cout << "insert " << key << " as new node\n";
        return new Node{key, nullptr, nullptr};
    }
    if (key < p->key) {
        cout << "insert " << key << ": go left of " << p->key << "\n";
        p->left = insert(p->left, key);
    } else if (key > p->key) {
        cout << "insert " << key << ": go right of " << p->key << "\n";
        p->right = insert(p->right, key);
    } else {
        cout << "insert " << key << ": duplicate, skip\n";
    }
    return p;
}

Node* search(Node* p, int key) {
    while (p) {
        cout << "search visit " << p->key << "\n";
        if (key == p->key) return p;
        p = (key < p->key) ? p->left : p->right;
    }
    return nullptr;
}

void inorder(Node* p) {
    if (!p) return;
    inorder(p->left);
    cout << p->key << " ";
    inorder(p->right);
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

    cout << "inorder: ";
    inorder(root);
    cout << "\n";

    cout << "search 6\n";
    if (search(root, 6)) cout << "found\n";
    else cout << "not found\n";

    cout << "search 7\n";
    if (search(root, 7)) cout << "found\n";
    else cout << "not found\n";

    // 空树查找
    if (!search(nullptr, 1)) cout << "empty search miss\n";

    freeTree(root);
    return 0;
}
