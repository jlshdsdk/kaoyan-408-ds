// AVL: LL then LR; four rotations; print inorder and balance factors
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int key;
    int h;
    Node* left;
    Node* right;
    Node(int k) : key(k), h(1), left(nullptr), right(nullptr) {}
};

int height(Node* p) { return p ? p->h : 0; }

void update(Node* p) {
    if (p) p->h = 1 + max(height(p->left), height(p->right));
}

int bf(Node* p) { return p ? height(p->left) - height(p->right) : 0; }

// RR: left rotate
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* t = y->left;
    y->left = x;
    x->right = t;
    update(x);
    update(y);
    return y;
}

// LL: right rotate
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* t = x->right;
    x->right = y;
    y->left = t;
    update(y);
    update(x);
    return x;
}

// LR: left on left-child, then right on root
Node* rotateLR(Node* z) {
    z->left = rotateLeft(z->left);
    return rotateRight(z);
}

// RL: right on right-child, then left on root
Node* rotateRL(Node* z) {
    z->right = rotateRight(z->right);
    return rotateLeft(z);
}

Node* insert(Node* root, int key) {
    if (!root) return new Node(key);
    if (key < root->key) root->left = insert(root->left, key);
    else if (key > root->key) root->right = insert(root->right, key);
    else return root;

    update(root);
    int b = bf(root);
    if (b > 1 && key < root->left->key) return rotateRight(root);      // LL
    if (b < -1 && key > root->right->key) return rotateLeft(root);     // RR
    if (b > 1 && key > root->left->key) return rotateLR(root);         // LR
    if (b < -1 && key < root->right->key) return rotateRL(root);       // RL
    return root;
}

void inorder(Node* p) {
    if (!p) return;
    inorder(p->left);
    cout << p->key << "(bf=" << bf(p) << ") ";
    inorder(p->right);
}

bool checkBF(Node* p) {
    if (!p) return true;
    int b = bf(p);
    if (b < -1 || b > 1) return false;
    if (p->h != 1 + max(height(p->left), height(p->right))) return false;
    return checkBF(p->left) && checkBF(p->right);
}

void freeTree(Node* p) {
    if (!p) return;
    freeTree(p->left);
    freeTree(p->right);
    delete p;
}

int main() {
    // LL: 30, 20, 10
    Node* t1 = nullptr;
    int ll[] = {30, 20, 10};
    for (int k : ll) t1 = insert(t1, k);
    cout << "LL inorder: ";
    inorder(t1);
    cout << "\n";
    cout << (checkBF(t1) ? "LL OK\n" : "LL BAD\n");

    // LR: 30, 10, 20
    Node* t2 = nullptr;
    int lr[] = {30, 10, 20};
    for (int k : lr) t2 = insert(t2, k);
    cout << "LR inorder: ";
    inorder(t2);
    cout << "\n";
    cout << (checkBF(t2) ? "LR OK\n" : "LR BAD\n");

    freeTree(t1);
    freeTree(t2);
    return 0;
}
