// 二叉树存储：顺序存储 + 链式存储，同一棵树 A(B(D,E),C(F))
#include <iostream>
using namespace std;

struct Node {
    char data;
    Node *l, *r;
    explicit Node(char c) : data(c), l(nullptr), r(nullptr) {}
};

void free_tree(Node* t) {
    if (!t) return;
    free_tree(t->l);
    free_tree(t->r);
    delete t;
}

int main() {
    // sequential: 1-based, empty as '#'
    // index: 1A 2B 3C 4D 5E 6F 7#
    const int CAP = 8;
    char seq[CAP] = {'#', 'A', 'B', 'C', 'D', 'E', 'F', '#'};

    cout << "seq=";
    for (int i = 1; i < CAP; i++) cout << seq[i];
    cout << "\n";
    for (int i = 1; i < CAP; i++) {
        if (seq[i] == '#') continue;
        cout << seq[i] << "@" << i;
        int L = 2 * i, R = 2 * i + 1;
        if (L < CAP) cout << " L=" << seq[L];
        if (R < CAP) cout << " R=" << seq[R];
        cout << "\n";
    }

    // linked: A(B(D,E),C(F))
    Node* A = new Node('A');
    Node* B = new Node('B');
    Node* C = new Node('C');
    Node* D = new Node('D');
    Node* E = new Node('E');
    Node* F = new Node('F');
    A->l = B; A->r = C;
    B->l = D; B->r = E;
    C->l = F;

    cout << "link A->" << A->l->data << "," << A->r->data << "\n";
    cout << "link B->" << B->l->data << "," << B->r->data << "\n";
    cout << "link C->" << C->l->data << ",#\n";
    cout << "link D->#,#\n";
    cout << "link E->#,#\n";
    cout << "link F->#,#\n";

    free_tree(A);
    return 0;
}
