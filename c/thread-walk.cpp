// Threaded binary tree: inorder next/prev and walk without a stack.
// Demo tree A(B(D,E),C). Inorder: D B E A C.
#include <iostream>
using namespace std;

struct Node {
    char data;
    Node* l;
    Node* r;
    bool ltag;  // false: child, true: thread
    bool rtag;
    Node(char d) : data(d), l(nullptr), r(nullptr), ltag(false), rtag(false) {}
};

Node* build() {
    Node* A = new Node('A');
    Node* B = new Node('B');
    Node* C = new Node('C');
    Node* D = new Node('D');
    Node* E = new Node('E');
    A->l = B;
    A->r = C;
    B->l = D;
    B->r = E;
    return A;
}

void thread_inorder(Node* p, Node*& pre) {
    if (!p) return;
    if (!p->ltag) thread_inorder(p->l, pre);
    if (!p->l) {
        p->ltag = true;
        p->l = pre;
    }
    if (pre && !pre->r) {
        pre->rtag = true;
        pre->r = p;
    }
    pre = p;
    if (!p->rtag) thread_inorder(p->r, pre);
}

Node* leftmost(Node* p) {
    if (!p) return nullptr;
    while (!p->ltag && p->l) p = p->l;
    return p;
}

// Inorder successor via thread or right-subtree leftmost.
Node* inorder_next(Node* p) {
    if (!p) return nullptr;
    if (p->rtag) return p->r;
    return leftmost(p->r);
}

// Inorder predecessor via thread or left-subtree rightmost.
Node* inorder_prev(Node* p) {
    if (!p) return nullptr;
    if (p->ltag) return p->l;
    Node* q = p->l;
    if (!q) return nullptr;
    while (!q->rtag && q->r) q = q->r;
    return q;
}

void inorder_walk(Node* root) {
    cout << "inorder walk:";
    for (Node* p = leftmost(root); p; p = inorder_next(p)) {
        cout << " " << p->data;
    }
    cout << "\n";
}

void free_tree(Node* p) {
    if (!p) return;
    if (!p->ltag) free_tree(p->l);
    if (!p->rtag) free_tree(p->r);
    delete p;
}

int main() {
    Node* root = build();
    Node* pre = nullptr;
    thread_inorder(root, pre);

    Node* E = root->l->r;  // E
    Node* D = root->l->l;  // D

    Node* succ = inorder_next(E);
    cout << "succ(E)=";
    if (succ) cout << succ->data;
    else cout << "null";
    cout << "\n";

    Node* pred = inorder_prev(D);
    cout << "pred(D)=";
    if (pred) cout << pred->data;
    else cout << "null";
    cout << "\n";

    inorder_walk(root);
    free_tree(root);
    return 0;
}
