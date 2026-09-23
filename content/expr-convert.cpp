// 中缀转后缀 / 前缀（运算符优先级 + 括号）
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAXS = 128;

int prec(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool isOp(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// 中缀转后缀（调度场算法）
bool infixToPostfix(const string& in, string& out) {
    char st[MAXS];
    int top = -1;
    out.clear();
    for (size_t i = 0; i < in.size(); i++) {
        char c = in[i];
        if (c == ' ') continue;
        if (c >= '0' && c <= '9') {
            if (!out.empty() && out.back() != ' ') out.push_back(' ');
            out.push_back(c);
        } else if (c == '(') {
            if (top >= MAXS - 1) {
                cout << "error\n";
                return false;
            }
            st[++top] = c;
        } else if (c == ')') {
            while (top >= 0 && st[top] != '(') {
                out.push_back(' ');
                out.push_back(st[top--]);
            }
            if (top < 0) {
                cout << "error\n";
                return false;
            }
            top--; // pop '('
        } else if (isOp(c)) {
            while (top >= 0 && isOp(st[top]) && prec(st[top]) >= prec(c)) {
                out.push_back(' ');
                out.push_back(st[top--]);
            }
            if (top >= MAXS - 1) {
                cout << "error\n";
                return false;
            }
            st[++top] = c;
        } else {
            cout << "error\n";
            return false;
        }
    }
    while (top >= 0) {
        if (st[top] == '(') {
            cout << "error\n";
            return false;
        }
        out.push_back(' ');
        out.push_back(st[top--]);
    }
    // trim leading space
    if (!out.empty() && out[0] == ' ') out.erase(0, 1);
    return true;
}

// 中缀转前缀：反转、括号对调、按后缀规则、再反转
string reverseSwapParen(const string& s) {
    string r;
    for (int i = (int)s.size() - 1; i >= 0; i--) {
        char c = s[i];
        if (c == '(') r.push_back(')');
        else if (c == ')') r.push_back('(');
        else r.push_back(c);
    }
    return r;
}

bool infixToPrefix(const string& in, string& out) {
    string rev = reverseSwapParen(in);
    string post;
    // 前缀转换时同级改为严格大于，保证结合性正确
    // 这里用改写后的调度：遇到同级不弹出（用临时改 prec 比较）
    char st[MAXS];
    int top = -1;
    post.clear();
    for (size_t i = 0; i < rev.size(); i++) {
        char c = rev[i];
        if (c == ' ') continue;
        if (c >= '0' && c <= '9') {
            if (!post.empty() && post.back() != ' ') post.push_back(' ');
            post.push_back(c);
        } else if (c == '(') {
            if (top >= MAXS - 1) {
                cout << "error\n";
                return false;
            }
            st[++top] = c;
        } else if (c == ')') {
            while (top >= 0 && st[top] != '(') {
                post.push_back(' ');
                post.push_back(st[top--]);
            }
            if (top < 0) {
                cout << "error\n";
                return false;
            }
            top--;
        } else if (isOp(c)) {
            while (top >= 0 && isOp(st[top]) && prec(st[top]) > prec(c)) {
                post.push_back(' ');
                post.push_back(st[top--]);
            }
            if (top >= MAXS - 1) {
                cout << "error\n";
                return false;
            }
            st[++top] = c;
        } else {
            cout << "error\n";
            return false;
        }
    }
    while (top >= 0) {
        if (st[top] == '(') {
            cout << "error\n";
            return false;
        }
        post.push_back(' ');
        post.push_back(st[top--]);
    }
    if (!post.empty() && post[0] == ' ') post.erase(0, 1);

    // 反转 token
    vector<string> toks;
    string cur;
    for (size_t i = 0; i <= post.size(); i++) {
        if (i == post.size() || post[i] == ' ') {
            if (!cur.empty()) toks.push_back(cur);
            cur.clear();
        } else cur.push_back(post[i]);
    }
    out.clear();
    for (int i = (int)toks.size() - 1; i >= 0; i--) {
        if (!out.empty()) out.push_back(' ');
        out += toks[i];
    }
    return true;
}

int main() {
    string in = "(2+3)*4";
    string post, pre;
    if (infixToPostfix(in, post)) cout << "postfix: " << post << "\n";
    if (infixToPrefix(in, pre)) cout << "prefix: " << pre << "\n";

    string bad = "(2+3";
    string tmp;
    if (!infixToPostfix(bad, tmp)) { /* unmatched */ }
    return 0;
}
