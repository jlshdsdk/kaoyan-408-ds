// 前序+中序推后序；后序+中序推前序
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    char v;
    Node* l;
    Node* r;
    Node(char c) : v(c), l(nullptr), r(nullptr) {}
};

void clear(Node* p) {
    if (!p) return;
    clear(p->l);
    clear(p->r);
    delete p;
}

int indexOf(const string& s, char c, int L, int R) {
    for (int i = L; i <= R; i++) if (s[i] == c) return i;
    return -1;
}

// 前序 + 中序 -> 建树
Node* buildPreIn(const string& pre, const string& in, int& pi, int L, int R) {
    if (L > R) return nullptr;
    if (pi >= (int)pre.size()) {
        cout << "error\n";
        return nullptr;
    }
    char root = pre[pi++];
    int k = indexOf(in, root, L, R);
    if (k < 0) {
        cout << "error\n";
        return nullptr;
    }
    Node* p = new Node(root);
    p->l = buildPreIn(pre, in, pi, L, k - 1);
    p->r = buildPreIn(pre, in, pi, k + 1, R);
    return p;
}

// 后序 + 中序 -> 建树（从后序末尾取根，先建右子树）
Node* buildPostIn(const string& post, const string& in, int& pi, int L, int R) {
    if (L > R) return nullptr;
    if (pi < 0) {
        cout << "error\n";
        return nullptr;
    }
    char root = post[pi--];
    int k = indexOf(in, root, L, R);
    if (k < 0) {
        cout << "error\n";
        return nullptr;
    }
    Node* p = new Node(root);
    p->r = buildPostIn(post, in, pi, k + 1, R);
    p->l = buildPostIn(post, in, pi, L, k - 1);
    return p;
}

void walkPre(Node* p, string& out) {
    if (!p) return;
    out.push_back(p->v);
    walkPre(p->l, out);
    walkPre(p->r, out);
}

void walkPost(Node* p, string& out) {
    if (!p) return;
    walkPost(p->l, out);
    walkPost(p->r, out);
    out.push_back(p->v);
}

string preInToPost(const string& pre, const string& in) {
    if (pre.size() != in.size() || pre.empty()) {
        cout << "error\n";
        return "";
    }
    int pi = 0;
    Node* root = buildPreIn(pre, in, pi, 0, (int)in.size() - 1);
    if (!root || pi != (int)pre.size()) {
        clear(root);
        cout << "error\n";
        return "";
    }
    string post;
    walkPost(root, post);
    clear(root);
    return post;
}

string postInToPre(const string& post, const string& in) {
    if (post.size() != in.size() || post.empty()) {
        cout << "error\n";
        return "";
    }
    int pi = (int)post.size() - 1;
    Node* root = buildPostIn(post, in, pi, 0, (int)in.size() - 1);
    if (!root || pi != -1) {
        clear(root);
        cout << "error\n";
        return "";
    }
    string pre;
    walkPre(root, pre);
    clear(root);
    return pre;
}

int main() {
    string pre = "ABDEGCFH";
    string in = "DBGEAFHC";
    string post = preInToPost(pre, in);
    cout << "postorder: " << post << "\n";

    string pre2 = postInToPre(post, in);
    cout << "preorder: " << pre2 << "\n";

    // mismatch
    string bad = postInToPre("ABC", "AB");
    (void)bad;
    return 0;
}
