// Red-black tree delete: build same as insert, then delete 20, full fixup
#include <iostream>
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

bool isRed(Node* p) { return p && p->color == RED; }
bool isBlack(Node* p) { return !p || p->color == BLACK; }

void rotateLeft(Node*& root, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rotateRight(Node*& root, Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right) x->right->parent = y;
    x->parent = y->parent;
    if (!y->parent) root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void insertFix(Node*& root, Node* z) {
    while (isRed(z->parent)) {
        Node* p = z->parent;
        Node* g = p->parent;
        if (p == g->left) {
            Node* u = g->right;
            if (isRed(u)) {
                p->color = BLACK;
                u->color = BLACK;
                g->color = RED;
                z = g;
            } else {
                if (z == p->right) {
                    z = p;
                    rotateLeft(root, z);
                    p = z->parent;
                    g = p->parent;
                }
                p->color = BLACK;
                g->color = RED;
                rotateRight(root, g);
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
                    rotateRight(root, z);
                    p = z->parent;
                    g = p->parent;
                }
                p->color = BLACK;
                g->color = RED;
                rotateLeft(root, g);
            }
        }
    }
    root->color = BLACK;
}

void insertKey(Node*& root, int key) {
    Node* z = new Node(key);
    Node* y = nullptr;
    Node* x = root;
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
    if (!y) root = z;
    else if (key < y->key) y->left = z;
    else y->right = z;
    insertFix(root, z);
}

// delete fixup: covers sibling red, sibling black + both kids black,
// near-red / far-red (black sibling) cases
void deleteFix(Node*& root, Node* x, Node* xp) {
    while ((!x || x->color == BLACK) && x != root) {
        if (x == (xp ? xp->left : nullptr)) {
            Node* w = xp->right;
            if (!w) {
                x = xp;
                xp = x ? x->parent : nullptr;
                continue;
            }
            if (isRed(w)) {
                // sibling red -> recolor + rotate, then sibling becomes black
                w->color = BLACK;
                xp->color = RED;
                rotateLeft(root, xp);
                w = xp->right;
            }
            if (isBlack(w->left) && isBlack(w->right)) {
                // sibling black, both children black
                w->color = RED;
                x = xp;
                xp = x ? x->parent : nullptr;
            } else {
                if (isBlack(w->right)) {
                    // near child red, far black
                    if (w->left) w->left->color = BLACK;
                    w->color = RED;
                    rotateRight(root, w);
                    w = xp->right;
                }
                // far child red
                w->color = xp->color;
                xp->color = BLACK;
                if (w->right) w->right->color = BLACK;
                rotateLeft(root, xp);
                x = root;
                xp = nullptr;
            }
        } else {
            Node* w = xp->left;
            if (!w) {
                x = xp;
                xp = x ? x->parent : nullptr;
                continue;
            }
            if (isRed(w)) {
                w->color = BLACK;
                xp->color = RED;
                rotateRight(root, xp);
                w = xp->left;
            }
            if (isBlack(w->left) && isBlack(w->right)) {
                w->color = RED;
                x = xp;
                xp = x ? x->parent : nullptr;
            } else {
                if (isBlack(w->left)) {
                    if (w->right) w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft(root, w);
                    w = xp->left;
                }
                w->color = xp->color;
                xp->color = BLACK;
                if (w->left) w->left->color = BLACK;
                rotateRight(root, xp);
                x = root;
                xp = nullptr;
            }
        }
    }
    if (x) x->color = BLACK;
}

void transplant(Node*& root, Node* u, Node* v) {
    if (!u->parent) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    if (v) v->parent = u->parent;
}

Node* treeMin(Node* p) {
    while (p->left) p = p->left;
    return p;
}

void deleteKey(Node*& root, int key) {
    Node* z = root;
    while (z && z->key != key) {
        if (key < z->key) z = z->left;
        else z = z->right;
    }
    if (!z) {
        cout << "error\n";
        return;
    }
    Node* y = z;
    Color yOrig = y->color;
    Node* x = nullptr;
    Node* xp = nullptr;
    if (!z->left) {
        x = z->right;
        xp = z->parent;
        transplant(root, z, z->right);
    } else if (!z->right) {
        x = z->left;
        xp = z->parent;
        transplant(root, z, z->left);
    } else {
        y = treeMin(z->right);
        yOrig = y->color;
        x = y->right;
        if (y->parent == z) {
            xp = y;
            if (x) x->parent = y;
        } else {
            xp = y->parent;
            transplant(root, y, y->right);
            y->right = z->right;
            if (y->right) y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        if (y->left) y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (yOrig == BLACK) deleteFix(root, x, xp);
}

void inorder(Node* p) {
    if (!p) return;
    inorder(p->left);
    cout << p->key << (p->color == RED ? "R" : "B") << " ";
    inorder(p->right);
}

bool noAdjRed(Node* p) {
    if (!p) return true;
    if (isRed(p) && (isRed(p->left) || isRed(p->right))) return false;
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
    Node* root = nullptr;
    int a[] = {10, 20, 30, 15, 25};
    for (int k : a) insertKey(root, k);

    cout << "before: ";
    inorder(root);
    cout << "\n";

    deleteKey(root, 20);

    cout << "after del 20: ";
    inorder(root);
    cout << "\n";
    cout << (checkRB(root) ? "OK\n" : "BAD\n");

    freeTree(root);
    return 0;
}
