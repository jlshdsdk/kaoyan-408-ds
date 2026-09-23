// 树 - 定义、术语、性质（普通树，非二叉树）
#include <iostream>
#include <vector>
using namespace std;

struct Node {
    char data;
    vector<Node*> kids;
    explicit Node(char c) : data(c) {}
};

int degree(const Node* t) {
    return t ? (int)t->kids.size() : 0;
}

int depth_of(const Node* t, char target, int d) {
    if (!t) return -1;
    if (t->data == target) return d;
    for (Node* k : t->kids) {
        int r = depth_of(k, target, d + 1);
        if (r >= 0) return r;
    }
    return -1;
}

int height(const Node* t) {
    if (!t) return -1;
    if (t->kids.empty()) return 0;
    int best = 0;
    for (Node* k : t->kids) {
        int h = height(k);
        if (h + 1 > best) best = h + 1;
    }
    return best;
}

void collect_leaves(const Node* t, vector<char>& out) {
    if (!t) return;
    if (t->kids.empty()) {
        out.push_back(t->data);
        return;
    }
    for (Node* k : t->kids) collect_leaves(k, out);
}

int count_nodes(const Node* t) {
    if (!t) return 0;
    int n = 1;
    for (Node* k : t->kids) n += count_nodes(k);
    return n;
}

int sum_degrees(const Node* t) {
    if (!t) return 0;
    int s = degree(t);
    for (Node* k : t->kids) s += sum_degrees(k);
    return s;
}

void free_tree(Node* t) {
    if (!t) return;
    for (Node* k : t->kids) free_tree(k);
    delete t;
}

int main() {
    // A has B C D; B has E F
    Node* A = new Node('A');
    Node* B = new Node('B');
    Node* C = new Node('C');
    Node* D = new Node('D');
    Node* E = new Node('E');
    Node* F = new Node('F');
    A->kids = {B, C, D};
    B->kids = {E, F};

    cout << "root=" << A->data << "\n";
    cout << "deg(A)=" << degree(A) << " deg(B)=" << degree(B)
         << " deg(C)=" << degree(C) << "\n";

    vector<char> leaves;
    collect_leaves(A, leaves);
    cout << "leaves=";
    for (char c : leaves) cout << c;
    cout << "\n";

    cout << "depth(E)=" << depth_of(A, 'E', 0) << "\n";
    cout << "height(tree)=" << height(A) << "\n";

    int n = count_nodes(A);
    int sd = sum_degrees(A);
    // n = sum(degree) + 1  (edges = sum degrees, nodes = edges + 1)
    cout << "nodes=" << n << " sum_deg=" << sd
         << " check_n=" << (sd + 1) << "\n";

    // remove root -> forest of trees rooted at B, C, D
    cout << "forest_roots=";
    for (Node* k : A->kids) cout << k->data;
    cout << "\n";

    free_tree(A);
    return 0;
}
