// Hash table: H(key)=key%7, chain resolve, successful ASL
#include <iostream>
#include <iomanip>
using namespace std;

const int M = 7;

struct Node {
    int key;
    Node* next;
    Node(int k) : key(k), next(nullptr) {}
};

int H(int key) { return key % M; }

void insert(Node* table[], int key) {
    int b = H(key);
    Node* p = new Node(key);
    p->next = table[b];
    table[b] = p;
    cout << "ins " << key << " -> bucket " << b << "\n";
}

Node* find(Node* table[], int key, int& comps) {
    comps = 0;
    int b = H(key);
    for (Node* p = table[b]; p; p = p->next) {
        comps++;
        if (p->key == key) return p;
    }
    return nullptr;
}

double successASL(Node* table[], const int keys[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        int c = 0;
        find(table, keys[i], c);
        sum += c;
    }
    return n ? (double)sum / n : 0.0;
}

void printTable(Node* table[]) {
    for (int i = 0; i < M; i++) {
        cout << "[" << i << "]";
        for (Node* p = table[i]; p; p = p->next) cout << "->" << p->key;
        cout << "\n";
    }
}

void freeTable(Node* table[]) {
    for (int i = 0; i < M; i++) {
        Node* p = table[i];
        while (p) {
            Node* q = p->next;
            delete p;
            p = q;
        }
        table[i] = nullptr;
    }
}

int main() {
    Node* table[M] = {};
    int keys[] = {14, 8, 21, 15, 7};
    int n = 5;
    for (int i = 0; i < n; i++) insert(table, keys[i]);
    printTable(table);

    double asl = successASL(table, keys, n);
    cout << fixed << setprecision(2);
    cout << "ASL_success=" << asl << "\n";

    int c = 0;
    if (!find(table, 99, c)) cout << "find(99)=miss comps=" << c << "\n";

    freeTable(table);
    return 0;
}
