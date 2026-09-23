// 基数排序代码（链式）：10 个桶用链表，LSD
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int v) : data(v), next(nullptr) {}
};

void printList(Node* head) {
    for (Node* p = head; p; p = p->next) {
        if (p != head) cout << " ";
        cout << p->data;
    }
    cout << "\n";
}

void clearList(Node*& head) {
    while (head) {
        Node* t = head;
        head = head->next;
        delete t;
    }
}

// 按 exp 位分配到 10 个链桶，再按 0..9 收集成新链表
Node* radixPass(Node* head, int exp) {
    Node* front[10] = {nullptr};
    Node* rear[10] = {nullptr};

    while (head) {
        Node* cur = head;
        head = head->next;
        cur->next = nullptr;
        int d = (cur->data / exp) % 10;
        if (!front[d]) {
            front[d] = rear[d] = cur;
        } else {
            rear[d]->next = cur;
            rear[d] = cur;
        }
    }

    Node* newHead = nullptr;
    Node* newTail = nullptr;
    for (int d = 0; d < 10; d++) {
        if (!front[d]) continue;
        if (!newHead) {
            newHead = front[d];
            newTail = rear[d];
        } else {
            newTail->next = front[d];
            newTail = rear[d];
        }
    }
    return newHead;
}

int main() {
    int raw[] = {21, 15, 8, 32, 4, 27};
    int n = 6;
    Node* head = nullptr;
    Node* tail = nullptr;
    for (int i = 0; i < n; i++) {
        Node* p = new Node(raw[i]);
        if (!head) head = tail = p;
        else {
            tail->next = p;
            tail = p;
        }
    }

    cout << "init: ";
    printList(head);

    head = radixPass(head, 1);   // 个位
    cout << "ones: ";
    printList(head);

    head = radixPass(head, 10);  // 十位
    cout << "tens: ";
    printList(head);

    clearList(head);
    return 0;
}
