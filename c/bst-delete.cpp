// 二叉搜索树删除：叶子 / 单孩子 / 双孩子（中序后继）
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
    return p;
}

void inorder(Node* p) {
    if (!p) return;
    inorder(p->left);
    cout << p->key << " ";
    inorder(p->right);
}

// 找右子树最小（中序后继）
Node* minNode(Node* p) {
    while (p && p->left) p = p->left;
    return p;
}

Node* remove(Node* p, int key) {
    if (!p) {
        cout << "delete " << key << ": not found\n";
        return nullptr;
    }
    if (key < p->key) {
        p->left = remove(p->left, key);
    } else if (key > p->key) {
        p->right = remove(p->right, key);
    } else {
        // 情况1：叶子（左右皆空）
        if (!p->left && !p->right) {
            cout << "delete " << key << ": leaf\n";
            delete p;
            return nullptr;
        }
        // 情况2：只有右孩子
        if (!p->left && p->right) {
            cout << "delete " << key << ": only right child\n";
            Node* r = p->right;
            delete p;
            return r;
        }
        // 情况2b：只有左孩子
        if (p->left && !p->right) {
            cout << "delete " << key << ": only left child\n";
            Node* l = p->left;
            delete p;
            return l;
        }
        // 情况3：两个孩子，用中序后继顶上
        Node* succ = minNode(p->right);
        cout << "delete " << key << ": two children, successor="
             << succ->key << "\n";
        p->key = succ->key;
        p->right = remove(p->right, succ->key);
    }
    return p;
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

    cout << "init inorder: ";
    inorder(root);
    cout << "\n";

    // 删叶子 1
    root = remove(root, 1);
    cout << "after del 1: ";
    inorder(root);
    cout << "\n";

    // 删只有右孩子的 14
    root = remove(root, 14);
    cout << "after del 14: ";
    inorder(root);
    cout << "\n";

    // 删有两个孩子的 3（后继为 4）
    root = remove(root, 3);
    cout << "after del 3: ";
    inorder(root);
    cout << "\n";

    // 删不存在
    root = remove(root, 99);

    freeTree(root);
    return 0;
}
