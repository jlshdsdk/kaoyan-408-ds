// 单链表：定义、头插法、尾插法创建
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* newNode(int x) {
    Node* p = new Node;
    p->data = x;
    p->next = nullptr;
    return p;
}

void clear(Node*& head) {
    while (head) {
        Node* t = head;
        head = head->next;
        delete t;
    }
}

// 头插：每次插在头结点之后（带头结点）
Node* createHeadInsert(const int a[], int n) {
    Node* head = newNode(0); // 头结点，data 不用
    for (int i = 0; i < n; i++) {
        Node* p = newNode(a[i]);
        p->next = head->next;
        head->next = p;
    }
    return head;
}

// 尾插：维护尾指针
Node* createTailInsert(const int a[], int n) {
    Node* head = newNode(0);
    Node* tail = head;
    for (int i = 0; i < n; i++) {
        Node* p = newNode(a[i]);
        tail->next = p;
        tail = p;
    }
    return head;
}

void print(Node* head) {
    Node* p = head ? head->next : nullptr;
    while (p) {
        cout << p->data;
        if (p->next) cout << "->";
        p = p->next;
    }
    cout << "\n";
}

int main() {
    int a[] = {1, 2, 3};

    // 头插 1,2,3 -> 3->2->1
    Node* H = createHeadInsert(a, 3);
    cout << "head-insert: ";
    print(H);
    clear(H);

    // 尾插 1,2,3 -> 1->2->3
    Node* T = createTailInsert(a, 3);
    cout << "tail-insert: ";
    print(T);
    clear(T);

    // 空序列
    Node* E = createTailInsert(a, 0);
    cout << "empty: ";
    print(E);
    clear(E);
    return 0;
}
