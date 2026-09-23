// 由前序 + 中序构造二叉树
#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node *l, *r;
    explicit Node(char c) : data(c), l(nullptr), r(nullptr) {}
};

Node* build(const string& pre, const string& in) {
    if (pre.empty() || in.empty() || pre.size() != in.size()) return nullptr;
    char root = pre[0];
    size_t k = in.find(root);
    if (k == string::npos) {
        cout << "error\n";
        return nullptr;
    }
    Node* t = new Node(root);
    string inL = in.substr(0, k);
    string inR = in.substr(k + 1);
    string preL = pre.substr(1, inL.size());
    string preR = pre.substr(1 + inL.size());
    t->l = build(preL, inL);
    t->r = build(preR, inR);
    return t;
}

void preorder(Node* t) {
    if (!t) return;
    cout << t->data;
    preorder(t->l);
    preorder(t->r);
}

void inorder(Node* t) {
    if (!t) return;
    inorder(t->l);
    cout << t->data;
    inorder(t->r);
}

void free_tree(Node* t) {
    if (!t) return;
    free_tree(t->l);
    free_tree(t->r);
    delete t;
}

int main() {
    string pre = "ABDECF";
    string in = "DBEAFC";
    cout << "pre=" << pre << "\n";
    cout << "in=" << in << "\n";

    Node* root = build(pre, in);
    if (!root) return 0;

    cout << "built_pre=";
    preorder(root);
    cout << "\n";
    cout << "built_in=";
    inorder(root);
    cout << "\n";

    free_tree(root);
    return 0;
}
