// 单链表：查找、插入、删除
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

Node* createTail(const int a[], int n) {
    Node* head = newNode(0);
    Node* tail = head;
    for (int i = 0; i < n; i++) {
        Node* p = newNode(a[i]);
        tail->next = p;
        tail = p;
    }
    return head;
}

// 按值查找，返回结点指针；找不到返回 nullptr
Node* find(Node* head, int x) {
    if (!head) return nullptr;
    for (Node* p = head->next; p; p = p->next) {
        if (p->data == x) return p;
    }
    return nullptr;
}

// 在值为 pred 的结点后插入 x
bool insertAfter(Node* head, int pred, int x) {
    Node* p = find(head, pred);
    if (!p) {
        cout << "error\n";
        return false;
    }
    Node* q = newNode(x);
    q->next = p->next;
    p->next = q;
    return true;
}

// 删除值为 x 的首个结点
bool eraseValue(Node* head, int x) {
    if (!head) {
        cout << "error\n";
        return false;
    }
    Node* prev = head;
    while (prev->next && prev->next->data != x) prev = prev->next;
    if (!prev->next) {
        cout << "error\n";
        return false;
    }
    Node* doomed = prev->next;
    prev->next = doomed->next;
    delete doomed;
    return true;
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
    int a[] = {1, 2, 3, 4};
    Node* head = createTail(a, 4);
    cout << "init: ";
    print(head);

    // 查找 2
    Node* p = find(head, 2);
    if (p) cout << "find(2)=" << p->data << "\n";
    else cout << "error\n";

    // 在 2 后插入 9 -> 1->2->9->3->4
    if (insertAfter(head, 2, 9)) {
        cout << "after insert 9: ";
        print(head);
    }

    // 删除 3 -> 1->2->9->4
    if (eraseValue(head, 3)) {
        cout << "after erase 3: ";
        print(head);
    }

    if (!find(head, 99)) cout << "find(99)=null\n";
    if (!eraseValue(head, 99)) { /* not found */ }
    clear(head);
    return 0;
}
