// Red-black tree: 5 properties, insert 10 20 30 15 25, recolor + rotate
#include <iostream>
#include <algorithm>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int key;
    Color color;
    Node* left;
    Node* right;
    Node* parent;
    Node(int k) : key(k), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

Node* root = nullptr;

bool isRed(Node* p) { return p && p->color == RED; }
bool isBlack(Node* p) { return !p || p->color == BLACK; }

void rotateLeft(Node*& rootRef, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) rootRef = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rotateRight(Node*& rootRef, Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right) x->right->parent = y;
    x->parent = y->parent;
    if (!y->parent) rootRef = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void insertFix(Node*& rootRef, Node* z) {
    while (isRed(z->parent)) {
        Node* p = z->parent;
        Node* g = p->parent;
        if (p == g->left) {
            Node* u = g->right;
            if (isRed(u)) {
                // uncle red: recolor
                p->color = BLACK;
                u->color = BLACK;
                g->color = RED;
                z = g;
            } else {
                if (z == p->right) {
                    z = p;
                    rotateLeft(rootRef, z);
                    p = z->parent;
                    g = p->parent;
                }
                p->color = BLACK;
                g->color = RED;
                rotateRight(rootRef, g);
            }
        } else {
            Node* u = g->left;
            if (isRed(u)) {
                p->color = BLACK;
                u->color = BLACK;
                g->color = RED;
                z = g;
            } else {
                if (z == p->left) {
                    z = p;
                    rotateRight(rootRef, z);
                    p = z->parent;
                    g = p->parent;
                }
                p->color = BLACK;
                g->color = RED;
                rotateLeft(rootRef, g);
            }
        }
    }
    rootRef->color = BLACK;
}

void insertKey(Node*& rootRef, int key) {
    Node* z = new Node(key);
    Node* y = nullptr;
    Node* x = rootRef;
    while (x) {
        y = x;
        if (key < x->key) x = x->left;
        else if (key > x->key) x = x->right;
        else {
            delete z;
            return;
        }
    }
    z->parent = y;
    if (!y) rootRef = z;
    else if (key < y->key) y->left = z;
    else y->right = z;
    insertFix(rootRef, z);
}

void inorder(Node* p) {
    if (!p) return;
    inorder(p->left);
    cout << p->key << (p->color == RED ? "R" : "B") << " ";
    inorder(p->right);
}

bool noAdjRed(Node* p) {
    if (!p) return true;
    if (isRed(p)) {
        if (isRed(p->left) || isRed(p->right)) return false;
    }
    return noAdjRed(p->left) && noAdjRed(p->right);
}

int blackHeight(Node* p, bool& ok) {
    if (!p) return 1;
    int L = blackHeight(p->left, ok);
    int R = blackHeight(p->right, ok);
    if (L != R) ok = false;
    return L + (p->color == BLACK ? 1 : 0);
}

bool checkRB(Node* r) {
    if (!r) return true;
    if (r->color != BLACK) return false;
    if (!noAdjRed(r)) return false;
    bool ok = true;
    blackHeight(r, ok);
    return ok;
}

void freeTree(Node* p) {
    if (!p) return;
    freeTree(p->left);
    freeTree(p->right);
    delete p;
}

int main() {
    root = nullptr;
    int a[] = {10, 20, 30, 15, 25};
    for (int k : a) insertKey(root, k);

    cout << "inorder: ";
    inorder(root);
    cout << "\n";
    cout << (checkRB(root) ? "RB OK\n" : "RB BAD\n");
    // properties: root black, no adj red, equal black-height, NIL black

    freeTree(root);
    root = nullptr;
    return 0;
}
