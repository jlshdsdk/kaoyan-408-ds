// 线索二叉树（上）：概念与中序线索化（ltag/rtag）
#include <iostream>
using namespace std;

struct Node {
    char data;
    Node *l, *r;
    int ltag; // 0: child, 1: thread
    int rtag;
    explicit Node(char c)
        : data(c), l(nullptr), r(nullptr), ltag(0), rtag(0) {}
};

Node* pre = nullptr;

void in_thread(Node* t) {
    if (!t) return;
    in_thread(t->l);
    if (!t->l) {
        t->ltag = 1;
        t->l = pre;
    }
    if (pre && !pre->r) {
        pre->rtag = 1;
        pre->r = t;
    }
    pre = t;
    in_thread(t->r);
}

void free_tree(Node* t) {
    if (!t) return;
    if (t->ltag == 0) free_tree(t->l);
    if (t->rtag == 0) free_tree(t->r);
    delete t;
}

void print_tags(Node* t) {
    if (!t) return;
    if (t->ltag == 0) print_tags(t->l);
    cout << t->data
         << " ltag=" << t->ltag
         << " rtag=" << t->rtag;
    if (t->ltag == 1) {
        cout << " Lthr=";
        if (t->l) cout << t->l->data;
        else cout << "#";
    }
    if (t->rtag == 1) {
        cout << " Rthr=";
        if (t->r) cout << t->r->data;
        else cout << "#";
    }
    cout << "\n";
    if (t->rtag == 0) print_tags(t->r);
}

int main() {
    // A(B(D,E),C)  -- inorder: D B E A C
    Node* A = new Node('A');
    Node* B = new Node('B');
    Node* C = new Node('C');
    Node* D = new Node('D');
    Node* E = new Node('E');
    A->l = B; A->r = C;
    B->l = D; B->r = E;

    pre = nullptr;
    in_thread(A);
    // last node C has null right -> keep as thread to null
    if (pre && !pre->r) {
        pre->rtag = 1;
        pre->r = nullptr;
    }

    cout << "inorder_threads\n";
    print_tags(A);

    // note: preorder/postorder threading use same ltag/rtag idea
    cout << "also: pre/post thread possible\n";

    free_tree(A);
    return 0;
}
