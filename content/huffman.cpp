// Huffman tree + prefix codes. Weights A:5 B:3 C:2 D:7 E:9.
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

struct Node {
    char ch;      // '\0' for internal
    int w;
    Node* l;
    Node* r;
    Node(char c, int weight) : ch(c), w(weight), l(nullptr), r(nullptr) {}
};

struct Cmp {
    bool operator()(const Node* a, const Node* b) const {
        if (a->w != b->w) return a->w > b->w;
        bool al = a->ch >= 'A' && a->ch <= 'Z';
        bool bl = b->ch >= 'A' && b->ch <= 'Z';
        if (al != bl) return !al;  // prefer leaf over internal
        return a->ch > b->ch;
    }
};

void encode(Node* p, const string& path, vector<string>& codes) {
    if (!p) return;
    if (!p->l && !p->r) {
        if (p->ch >= 'A' && p->ch <= 'E') {
            codes[p->ch - 'A'] = path.empty() ? "0" : path;
        }
        return;
    }
    encode(p->l, path + "0", codes);
    encode(p->r, path + "1", codes);
}

int wpl(Node* p, int depth) {
    if (!p) return 0;
    if (!p->l && !p->r) return p->w * depth;
    return wpl(p->l, depth + 1) + wpl(p->r, depth + 1);
}

bool is_prefix_free(const vector<string>& codes) {
    for (size_t i = 0; i < codes.size(); ++i) {
        if (codes[i].empty()) continue;
        for (size_t j = 0; j < codes.size(); ++j) {
            if (i == j || codes[j].empty()) continue;
            if (codes[j].size() >= codes[i].size() &&
                codes[j].compare(0, codes[i].size(), codes[i]) == 0) {
                return false;
            }
        }
    }
    return true;
}

void free_tree(Node* p) {
    if (!p) return;
    free_tree(p->l);
    free_tree(p->r);
    delete p;
}

int main() {
    // A:5 B:3 C:2 D:7 E:9
    const char chars[] = {'A', 'B', 'C', 'D', 'E'};
    const int weights[] = {5, 3, 2, 7, 9};

    priority_queue<Node*, vector<Node*>, Cmp> pq;
    for (int i = 0; i < 5; ++i) {
        pq.push(new Node(chars[i], weights[i]));
    }

    cout << "merge steps:\n";
    while (pq.size() > 1) {
        Node* a = pq.top();
        pq.pop();
        Node* b = pq.top();
        pq.pop();
        Node* p = new Node('\0', a->w + b->w);
        p->l = a;
        p->r = b;
        cout << "  merge " << a->w << " + " << b->w << " -> " << p->w << "\n";
        pq.push(p);
    }

    Node* root = pq.top();
    vector<string> codes(5);
    encode(root, "", codes);

    cout << "codes:\n";
    for (int i = 0; i < 5; ++i) {
        cout << "  " << chars[i] << ": " << codes[i] << "\n";
    }
    int W = wpl(root, 0);
    cout << "WPL=" << W << "\n";
    cout << "prefix_ok=" << (is_prefix_free(codes) ? "yes" : "no") << "\n";

    free_tree(root);
    return 0;
}
