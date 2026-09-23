// 后缀表达式求值（顺带演示前缀：从右往左）
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

const int MAXS = 128;

struct IntStack {
    int a[MAXS];
    int top;
};

void stInit(IntStack& s) { s.top = -1; }
bool stEmpty(const IntStack& s) { return s.top < 0; }
bool stFull(const IntStack& s) { return s.top >= MAXS - 1; }

bool stPush(IntStack& s, int x) {
    if (stFull(s)) {
        cout << "error\n";
        return false;
    }
    s.a[++s.top] = x;
    return true;
}

bool stPop(IntStack& s, int& out) {
    if (stEmpty(s)) {
        cout << "error\n";
        return false;
    }
    out = s.a[s.top--];
    return true;
}

bool applyOp(char op, int a, int b, int& out) {
    if (op == '+') out = a + b;
    else if (op == '-') out = a - b;
    else if (op == '*') out = a * b;
    else if (op == '/') {
        if (b == 0) {
            cout << "error\n";
            return false;
        }
        out = a / b;
    } else {
        cout << "error\n";
        return false;
    }
    return true;
}

// 后缀：从左到右，遇运算数入栈，遇运算符弹两个算完再入栈
bool evalPostfix(const vector<string>& tok, int& result) {
    IntStack s;
    stInit(s);
    for (size_t i = 0; i < tok.size(); i++) {
        const string& t = tok[i];
        if (t.size() == 1 && (t[0] == '+' || t[0] == '-' || t[0] == '*' || t[0] == '/')) {
            int b = 0, a = 0, r = 0;
            if (!stPop(s, b) || !stPop(s, a)) return false;
            if (!applyOp(t[0], a, b, r)) return false;
            if (!stPush(s, r)) return false;
        } else {
            int v = 0;
            for (size_t k = 0; k < t.size(); k++) {
                if (!isdigit((unsigned char)t[k])) {
                    cout << "error\n";
                    return false;
                }
                v = v * 10 + (t[k] - '0');
            }
            if (!stPush(s, v)) return false;
        }
    }
    if (s.top != 0) {
        cout << "error\n";
        return false;
    }
    result = s.a[0];
    return true;
}

// 前缀：从右到左扫，规则对称
bool evalPrefix(const vector<string>& tok, int& result) {
    IntStack s;
    stInit(s);
    for (int i = (int)tok.size() - 1; i >= 0; i--) {
        const string& t = tok[i];
        if (t.size() == 1 && (t[0] == '+' || t[0] == '-' || t[0] == '*' || t[0] == '/')) {
            int a = 0, b = 0, r = 0;
            if (!stPop(s, a) || !stPop(s, b)) return false;
            if (!applyOp(t[0], a, b, r)) return false;
            if (!stPush(s, r)) return false;
        } else {
            int v = 0;
            for (size_t k = 0; k < t.size(); k++) {
                if (!isdigit((unsigned char)t[k])) {
                    cout << "error\n";
                    return false;
                }
                v = v * 10 + (t[k] - '0');
            }
            if (!stPush(s, v)) return false;
        }
    }
    if (s.top != 0) {
        cout << "error\n";
        return false;
    }
    result = s.a[0];
    return true;
}

int main() {
    // 后缀 2 3 + 4 * = (2+3)*4 = 20
    vector<string> post = {"2", "3", "+", "4", "*"};
    int r = 0;
    if (evalPostfix(post, r)) cout << "postfix=20? " << r << "\n";

    // 对应前缀 * + 2 3 4
    vector<string> pre = {"*", "+", "2", "3", "4"};
    if (evalPrefix(pre, r)) cout << "prefix=" << r << "\n";

    // 空表达式
    vector<string> empty;
    if (!evalPostfix(empty, r)) { /* error */ }
    return 0;
}
