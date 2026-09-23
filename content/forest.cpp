// Forest <-> binary tree via left-child / right-sibling.
// Forest: T1=A(B,C), T2=D(E). Preorder/postorder map to BT preorder/inorder.
#include <iostream>
using namespace std;

struct TNode {
    char data;
    TNode* child[4];
    int nchild;
    TNode(char d) : data(d), nchild(0) {
        for (int i = 0; i < 4; ++i) child[i] = nullptr;
    }
};

struct BNode {
    char data;
    BNode* l;
    BNode* r;
    BNode(char d) : data(d), l(nullptr), r(nullptr) {}
};

BNode* tree_to_bt(TNode* t) {
    if (!t) return nullptr;
    BNode* b = new BNode(t->data);
    if (t->nchild > 0) b->l = tree_to_bt(t->child[0]);
    BNode* sib = b->l;
    for (int i = 1; i < t->nchild; ++i) {
        BNode* nb = tree_to_bt(t->child[i]);
        if (!sib) b->l = nb;
        else sib->r = nb;
        sib = nb;
    }
    return b;
}

// Link roots of trees as right-sibling chain.
BNode* forest_to_bt(TNode** roots, int n) {
    if (n <= 0 || !roots[0]) return nullptr;
    BNode* first = tree_to_bt(roots[0]);
    BNode* cur = first;
    for (int i = 1; i < n; ++i) {
        cur->r = tree_to_bt(roots[i]);
        cur = cur->r;
    }
    return first;
}

void preorder(BNode* p) {
    if (!p) return;
    cout << p->data;
    preorder(p->l);
    preorder(p->r);
}

void inorder(BNode* p) {
    if (!p) return;
    inorder(p->l);
    cout << p->data;
    inorder(p->r);
}

void free_tree(TNode* t) {
    if (!t) return;
    for (int i = 0; i < t->nchild; ++i) free_tree(t->child[i]);
    delete t;
}

void free_bt(BNode* p) {
    if (!p) return;
    free_bt(p->l);
    free_bt(p->r);
    delete p;
}

int main() {
    TNode* A = new TNode('A');
    TNode* B = new TNode('B');
    TNode* C = new TNode('C');
    A->child[A->nchild++] = B;
    A->child[A->nchild++] = C;

    TNode* D = new TNode('D');
    TNode* E = new TNode('E');
    D->child[D->nchild++] = E;

    TNode* roots[2] = {A, D};
    BNode* bt = forest_to_bt(roots, 2);

    cout << "BT structure: A.l=B, B.r=C, A.r=D, D.l=E\n";
    cout << "forest preorder = BT preorder: ";
    preorder(bt);
    cout << "\n";
    cout << "forest postorder = BT inorder: ";
    inorder(bt);
    cout << "\n";

    free_bt(bt);
    free_tree(A);
    free_tree(D);
    return 0;
}
