// 二叉树遍历：前序、中序、后序、层序
#include <iostream>
#include <queue>
using namespace std;

struct Node {
    char data;
    Node *l, *r;
    explicit Node(char c) : data(c), l(nullptr), r(nullptr) {}
};

void preorder(Node* t) {
    if (!t) return;
    cout << t->data;
    preorder(t->l);
    preorder(t->r);
}

void inorder(Node* t) {
    if (!t) return;
    inorder(t->l);
    cout << t->data;
    inorder(t->r);
}

void postorder(Node* t) {
    if (!t) return;
    postorder(t->l);
    postorder(t->r);
    cout << t->data;
}

void levelorder(Node* t) {
    if (!t) return;
    queue<Node*> q;
    q.push(t);
    while (!q.empty()) {
        Node* cur = q.front();
        q.pop();
        cout << cur->data;
        if (cur->l) q.push(cur->l);
        if (cur->r) q.push(cur->r);
    }
}

void free_tree(Node* t) {
    if (!t) return;
    free_tree(t->l);
    free_tree(t->r);
    delete t;
}

int main() {
    // A(B(D,E),C(F))
    Node* A = new Node('A');
    Node* B = new Node('B');
    Node* C = new Node('C');
    Node* D = new Node('D');
    Node* E = new Node('E');
    Node* F = new Node('F');
    A->l = B; A->r = C;
    B->l = D; B->r = E;
    C->l = F;

    cout << "pre=";
    preorder(A);
    cout << "\n";
    cout << "in=";
    inorder(A);
    cout << "\n";
    cout << "post=";
    postorder(A);
    cout << "\n";
    cout << "level=";
    levelorder(A);
    cout << "\n";

    free_tree(A);
    return 0;
}
