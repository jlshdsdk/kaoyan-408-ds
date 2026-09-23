// B-tree m=3 delete: remove first, then fix underflow (borrow / merge)
#include <iostream>
#include <vector>
using namespace std;

const int M = 3;
const int MAX_KEY = M - 1; // 2
const int MIN_KEY = 1;

struct Node {
    int n;
    int key[M];
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
            if (!p->leaf)
                for (int i = 0; i <= p->n; i++)
                    if (p->child[i]) next.push_back(p->child[i]);
        }
        cout << "\n";
        q = next;
        level++;
    }
}

void splitNode(Node* y, int& up, Node*& z) {
    int mid = 1;
    up = y->key[mid];
    z = new Node();
    z->leaf = y->leaf;
    z->n = y->n - mid - 1;
    for (int j = 0; j < z->n; j++) z->key[j] = y->key[mid + 1 + j];
    if (!y->leaf)
        for (int j = 0; j <= z->n; j++) z->child[j] = y->child[mid + 1 + j];
    y->n = mid;
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

void borrowFromLeft(Node* parent, int idx) {
    Node* cur = parent->child[idx];
    Node* left = parent->child[idx - 1];
    for (int i = cur->n; i > 0; i--) cur->key[i] = cur->key[i - 1];
    if (!cur->leaf) {
        for (int i = cur->n + 1; i > 0; i--) cur->child[i] = cur->child[i - 1];
        cur->child[0] = left->child[left->n];
    }
    cur->key[0] = parent->key[idx - 1];
    cur->n++;
    parent->key[idx - 1] = left->key[left->n - 1];
    left->n--;
}

void borrowFromRight(Node* parent, int idx) {
    Node* cur = parent->child[idx];
    Node* right = parent->child[idx + 1];
    cur->key[cur->n] = parent->key[idx];
    if (!cur->leaf) cur->child[cur->n + 1] = right->child[0];
    cur->n++;
    parent->key[idx] = right->key[0];
    for (int i = 1; i < right->n; i++) right->key[i - 1] = right->key[i];
    if (!right->leaf) {
        for (int i = 1; i <= right->n; i++) right->child[i - 1] = right->child[i];
    }
    right->n--;
}

// merge child idx with right sibling; works when left may be empty (n=0)
void mergeWithRight(Node* parent, int idx) {
    Node* left = parent->child[idx];
    Node* right = parent->child[idx + 1];
    int Ln = left->n;
    left->key[Ln] = parent->key[idx];
    for (int i = 0; i < right->n; i++) left->key[Ln + 1 + i] = right->key[i];
    if (!left->leaf) {
        for (int i = 0; i <= right->n; i++)
            left->child[Ln + 1 + i] = right->child[i];
    }
    left->n = Ln + 1 + right->n;
    for (int i = idx + 1; i < parent->n; i++) {
        parent->key[i - 1] = parent->key[i];
        parent->child[i] = parent->child[i + 1];
    }
    if (parent->n > 0) parent->child[parent->n] = nullptr;
    parent->n--;
    delete right;
}

void fixUnderflow(Node* parent, int idx) {
    if (idx > 0 && parent->child[idx - 1]->n > MIN_KEY)
        borrowFromLeft(parent, idx);
    else if (idx < parent->n && parent->child[idx + 1]->n > MIN_KEY)
        borrowFromRight(parent, idx);
    else if (idx < parent->n)
        mergeWithRight(parent, idx);
    else
        mergeWithRight(parent, idx - 1);
}

int getPred(Node* x) {
    while (!x->leaf) x = x->child[x->n];
    return x->key[x->n - 1];
}

int getSucc(Node* x) {
    while (!x->leaf) x = x->child[0];
    return x->key[0];
}

bool deleteFrom(Node* x, int k);

bool deleteFrom(Node* x, int k) {
    int i = 0;
    while (i < x->n && x->key[i] < k) i++;

    if (x->leaf) {
        if (i >= x->n || x->key[i] != k) {
            cout << "error\n";
            return false;
        }
        for (int j = i + 1; j < x->n; j++) x->key[j - 1] = x->key[j];
        x->n--;
        return true;
    }

    if (i < x->n && x->key[i] == k) {
        // key in internal: replace with pred or succ, delete that instead
        if (x->child[i]->n >= MIN_KEY) {
            int pred = getPred(x->child[i]);
            x->key[i] = pred;
            deleteFrom(x->child[i], pred);
            if (x->child[i]->n < MIN_KEY) fixUnderflow(x, i);
        } else if (x->child[i + 1]->n >= MIN_KEY) {
            int succ = getSucc(x->child[i + 1]);
            x->key[i] = succ;
            deleteFrom(x->child[i + 1], succ);
            if (x->child[i + 1]->n < MIN_KEY) fixUnderflow(x, i + 1);
        } else {
            mergeWithRight(x, i);
            deleteFrom(x->child[i], k);
            if (x->child[i]->n < MIN_KEY) fixUnderflow(x, i);
        }
        return true;
    }

    int ci = i;
    bool ok = deleteFrom(x->child[ci], k);
    if (!ok) return false;
    if (x->child[ci]->n < MIN_KEY) {
        // after merge with left, underflown slot may become ci-1
        int before = x->n;
        fixUnderflow(x, ci);
        if (x->n < before && ci > 0 && ci - 1 <= x->n) {
            // merged into left; child[ci] gone — already fixed
        }
    }
    return true;
}

void deleteKey(int k) {
    if (!root) {
        cout << "error\n";
        return;
    }
    deleteFrom(root, k);
    if (root && root->n == 0) {
        Node* old = root;
        if (!root->leaf) root = root->child[0];
        else root = nullptr;
        delete old;
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
    for (int k : a) insertKey(k);
    cout << "built:\n";
    printLevels(root);

    // 1) leaf delete + borrow: del 12, left [5 6] lends
    deleteKey(12);
    cout << "after del 12 (borrow):\n";
    printLevels(root);
    bool ok1 = checkNode(root, true) && countKeys(root) == 5;

    // 2) leaf delete + merge: del 5, empty merges with neighbor
    deleteKey(5);
    cout << "after del 5 (merge):\n";
    printLevels(root);
    bool ok2 = checkNode(root, true) && countKeys(root) == 4;

    cout << ((ok1 && ok2) ? "B-delete OK\n" : "B-delete BAD\n");
    freeTree(root);
    root = nullptr;
    return 0;
}
