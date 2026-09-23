// Tree storage: parent array, children lists, child-sibling links.
// Tree: A with children B,C; B with child D.
#include <iostream>
#include <vector>
using namespace std;

struct ParentNode {
    char data;
    int parent;  // -1 for root
};

struct ChildNode {
    int child;
    ChildNode* next;
    ChildNode(int c) : child(c), next(nullptr) {}
};

struct ChildHead {
    char data;
    ChildNode* first;
};

struct CSNode {
    char data;
    CSNode* first_child;
    CSNode* next_sibling;
    CSNode(char d) : data(d), first_child(nullptr), next_sibling(nullptr) {}
};

void print_parent(const vector<ParentNode>& t) {
    cout << "parent:\n";
    for (size_t i = 0; i < t.size(); ++i) {
        cout << "  " << t[i].data << " parent=";
        if (t[i].parent < 0) cout << "none";
        else cout << t[t[i].parent].data;
        cout << "\n";
    }
}

void print_children(const vector<ChildHead>& t) {
    cout << "children:\n";
    for (size_t i = 0; i < t.size(); ++i) {
        cout << "  " << t[i].data << ":";
        for (ChildNode* p = t[i].first; p; p = p->next) {
            cout << " " << t[p->child].data;
        }
        cout << "\n";
    }
}

void print_cs(CSNode* p, int depth) {
    if (!p) return;
    for (int i = 0; i < depth; ++i) cout << "  ";
    cout << p->data << "\n";
    print_cs(p->first_child, depth + 1);
    print_cs(p->next_sibling, depth);
}

void free_children(vector<ChildHead>& t) {
    for (auto& h : t) {
        ChildNode* p = h.first;
        while (p) {
            ChildNode* n = p->next;
            delete p;
            p = n;
        }
        h.first = nullptr;
    }
}

void free_cs(CSNode* p) {
    if (!p) return;
    free_cs(p->first_child);
    free_cs(p->next_sibling);
    delete p;
}

int main() {
    // indices: 0:A 1:B 2:C 3:D
    vector<ParentNode> parent = {
        {'A', -1},
        {'B', 0},
        {'C', 0},
        {'D', 1}
    };
    print_parent(parent);

    vector<ChildHead> kids(4);
    kids[0] = {'A', new ChildNode(1)};
    kids[0].first->next = new ChildNode(2);
    kids[1] = {'B', new ChildNode(3)};
    kids[2] = {'C', nullptr};
    kids[3] = {'D', nullptr};
    print_children(kids);

    CSNode* A = new CSNode('A');
    CSNode* B = new CSNode('B');
    CSNode* C = new CSNode('C');
    CSNode* D = new CSNode('D');
    A->first_child = B;
    B->next_sibling = C;
    B->first_child = D;
    cout << "child-sibling:\n";
    print_cs(A, 1);

    free_children(kids);
    free_cs(A);
    return 0;
}
