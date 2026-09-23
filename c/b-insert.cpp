// B-tree order m=3 (max 2 keys); insert then split on overflow
#include <iostream>
#include <vector>
using namespace std;

const int M = 3;           // order
const int MAX_KEY = M - 1; // 2
const int MIN_KEY = 1;

struct Node {
    int n;
    int key[M]; // allow temporary n==M (3)
    Node* child[M + 1];
    bool leaf;
    Node() : n(0), leaf(true) {
        for (int i = 0; i < M; i++) key[i] = 0;
        for (int i = 0; i <= M; i++) child[i] = nullptr;
    }
};

Node* root = nullptr;

void printLevels(Node* r) {
    if (!r) {
        cout << "(empty)\n";
        return;
    }
    vector<Node*> q;
    q.push_back(r);
    int level = 0;
    while (!q.empty()) {
        cout << "L" << level << ":";
        vector<Node*> next;
        for (Node* p : q) {
            cout << " [";
            for (int i = 0; i < p->n; i++) {
                if (i) cout << " ";
                cout << p->key[i];
            }
            cout << "]";
            if (!p->leaf) {
                for (int i = 0; i <= p->n; i++)
                    if (p->child[i]) next.push_back(p->child[i]);
            }
        }
        cout << "\n";
        q = next;
        level++;
    }
}

// y has n==M (3 keys); median key[1] goes up; right sibling returned
void splitNode(Node* y, int& up, Node*& z) {
    int mid = 1;
    up = y->key[mid];
    z = new Node();
    z->leaf = y->leaf;
    z->n = y->n - mid - 1; // 1
    for (int j = 0; j < z->n; j++) z->key[j] = y->key[mid + 1 + j];
    if (!y->leaf) {
        for (int j = 0; j <= z->n; j++) z->child[j] = y->child[mid + 1 + j];
    }
    y->n = mid; // 1
}

void insertInto(Node* x, int k) {
    if (x->leaf) {
        int i = x->n - 1;
        while (i >= 0 && k < x->key[i]) {
            x->key[i + 1] = x->key[i];
            i--;
        }
        x->key[i + 1] = k;
        x->n++;
        return;
    }
    int i = x->n - 1;
    while (i >= 0 && k < x->key[i]) i--;
    i++;
    insertInto(x->child[i], k);
    if (x->child[i]->n == M) {
        int up;
        Node* z;
        splitNode(x->child[i], up, z);
        for (int j = x->n; j > i; j--) {
            x->key[j] = x->key[j - 1];
            x->child[j + 1] = x->child[j];
        }
        x->key[i] = up;
        x->child[i + 1] = z;
        x->n++;
    }
}

void insertKey(int k) {
    if (!root) {
        root = new Node();
        root->key[0] = k;
        root->n = 1;
        return;
    }
    insertInto(root, k);
    if (root->n == M) {
        Node* s = new Node();
        s->leaf = false;
        int up;
        Node* z;
        splitNode(root, up, z);
        s->key[0] = up;
        s->child[0] = root;
        s->child[1] = z;
        s->n = 1;
        root = s;
    }
}

int countKeys(Node* p) {
    if (!p) return 0;
    int s = p->n;
    if (!p->leaf)
        for (int i = 0; i <= p->n; i++) s += countKeys(p->child[i]);
    return s;
}

bool checkNode(Node* p, bool isRoot) {
    if (!p) return true;
    if (p->n < 0 || p->n > MAX_KEY) return false;
    if (!isRoot && p->n < MIN_KEY) return false;
    for (int i = 1; i < p->n; i++)
        if (p->key[i - 1] >= p->key[i]) return false;
    if (!p->leaf)
        for (int i = 0; i <= p->n; i++)
            if (!checkNode(p->child[i], false)) return false;
    return true;
}

void freeTree(Node* p) {
    if (!p) return;
    if (!p->leaf)
        for (int i = 0; i <= p->n; i++) freeTree(p->child[i]);
    delete p;
}

int main() {
    int a[] = {10, 20, 5, 6, 12, 30};
    for (int k : a) {
        insertKey(k);
        cout << "after " << k << ":\n";
        printLevels(root);
    }
    bool ok = checkNode(root, true) && countKeys(root) == 6;
    cout << (ok ? "B-insert OK keys=6\n" : "B-insert BAD\n");
    freeTree(root);
    root = nullptr;
    return 0;
}
