// B+ tree order 3: keys in leaves + leaf linked list; insert 5 8 10 15 20
#include <iostream>
using namespace std;

const int ORDER = 3;
const int MAX_KEY = ORDER - 1; // 2

struct Leaf {
    int n;
    int key[ORDER]; // temp overflow to 3
    Leaf* next;
    Leaf() : n(0), next(nullptr) {
        for (int i = 0; i < ORDER; i++) key[i] = 0;
    }
};

struct Internal {
    int n;
    int key[ORDER];
    void* child[ORDER + 1]; // Leaf* or Internal*
    bool childIsLeaf;
    Internal() : n(0), childIsLeaf(true) {
        for (int i = 0; i < ORDER; i++) key[i] = 0;
        for (int i = 0; i <= ORDER; i++) child[i] = nullptr;
    }
};

Internal* root = nullptr;
Leaf* head = nullptr; // leftmost leaf

void printLeafChain() {
    cout << "leaves:";
    for (Leaf* p = head; p; p = p->next) {
        cout << " [";
        for (int i = 0; i < p->n; i++) {
            if (i) cout << " ";
            cout << p->key[i];
        }
        cout << "]";
    }
    cout << "\n";
}

int countLeafKeys() {
    int s = 0;
    for (Leaf* p = head; p; p = p->next) s += p->n;
    return s;
}

// split full leaf (n==3); copy separator (min of right) up
void splitLeaf(Leaf* L, int& upKey, Leaf*& right) {
    right = new Leaf();
    // left keeps 1 key, right gets 2; upKey = min(right)
    L->n = 1;
    right->n = 2;
    right->key[0] = L->key[1];
    right->key[1] = L->key[2];
    upKey = right->key[0];
    right->next = L->next;
    L->next = right;
}

void insertIntoLeaf(Leaf* L, int k) {
    int i = L->n - 1;
    while (i >= 0 && k < L->key[i]) {
        L->key[i + 1] = L->key[i];
        i--;
    }
    L->key[i + 1] = k;
    L->n++;
}

// insert separator into internal; may overflow
void insertSep(Internal* node, int sep, void* rightChild, int childIndex) {
    for (int j = node->n; j > childIndex; j--) {
        node->key[j] = node->key[j - 1];
        node->child[j + 1] = node->child[j];
    }
    node->key[childIndex] = sep;
    node->child[childIndex + 1] = rightChild;
    node->n++;
}

bool insertRecursive(Internal* node, int k, int& upKey, void*& upRight);

bool insertRecursive(Internal* node, int k, int& upKey, void*& upRight) {
    upRight = nullptr;
    if (node->childIsLeaf) {
        int i = 0;
        while (i < node->n && k >= node->key[i]) i++;
        Leaf* L = (Leaf*)node->child[i];
        insertIntoLeaf(L, k);
        if (L->n <= MAX_KEY) return false;
        Leaf* R;
        int sep;
        splitLeaf(L, sep, R);
        insertSep(node, sep, R, i);
        if (node->n <= MAX_KEY) return false;
        // split internal
        Internal* nr = new Internal();
        nr->childIsLeaf = node->childIsLeaf;
        // node has 3 keys, 4 children; push middle up
        int mid = 1;
        upKey = node->key[mid];
        nr->n = 1;
        nr->key[0] = node->key[2];
        nr->child[0] = node->child[2];
        nr->child[1] = node->child[3];
        node->n = 1;
        upRight = nr;
        return true;
    }
    int i = 0;
    while (i < node->n && k >= node->key[i]) i++;
    int childUp;
    void* childRight;
    bool split = insertRecursive((Internal*)node->child[i], k, childUp, childRight);
    if (!split) return false;
    insertSep(node, childUp, childRight, i);
    if (node->n <= MAX_KEY) return false;
    Internal* nr = new Internal();
    nr->childIsLeaf = false;
    int mid = 1;
    upKey = node->key[mid];
    nr->n = 1;
    nr->key[0] = node->key[2];
    nr->child[0] = node->child[2];
    nr->child[1] = node->child[3];
    node->n = 1;
    upRight = nr;
    return true;
}

void insertKey(int k) {
    if (!head) {
        head = new Leaf();
        head->key[0] = k;
        head->n = 1;
        return;
    }
    if (!root) {
        // only one leaf
        insertIntoLeaf(head, k);
        if (head->n <= MAX_KEY) return;
        Leaf* R;
        int sep;
        splitLeaf(head, sep, R);
        root = new Internal();
        root->childIsLeaf = true;
        root->key[0] = sep;
        root->child[0] = head;
        root->child[1] = R;
        root->n = 1;
        return;
    }
    int upKey;
    void* upRight;
    bool split = insertRecursive(root, k, upKey, upRight);
    if (split) {
        Internal* nr = new Internal();
        nr->childIsLeaf = false;
        nr->key[0] = upKey;
        nr->child[0] = root;
        nr->child[1] = upRight;
        nr->n = 1;
        root = nr;
    }
}

int main() {
    int a[] = {5, 8, 10, 15, 20};
    for (int k : a) {
        insertKey(k);
        cout << "after " << k << " ";
        printLeafChain();
    }
    int total = countLeafKeys();
    bool ok = total == 5;
    // verify sorted along chain
    int prev = -1;
    for (Leaf* p = head; p && ok; p = p->next) {
        for (int i = 0; i < p->n; i++) {
            if (p->key[i] <= prev) ok = false;
            prev = p->key[i];
        }
    }
    cout << (ok ? "B+ OK\n" : "B+ BAD\n");
    return 0;
}
