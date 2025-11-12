#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int d) { data = d; next = NULL; }
};

void insertBeg(Node* &head, int x) {
    Node* t = new Node(x);
    t->next = head;
    head = t;
}

void insertEnd(Node* &head, int x) {
    Node* t = new Node(x);
    if (!head) { head = t; return; }
    Node* p = head;
    while (p->next) p = p->next;
    p->next = t;
}

void insertPos(Node* &head, int pos, int x) {
    if (pos == 0) { insertBeg(head, x); return; }
    Node* p = head;
    for (int i = 0; i < pos - 1 && p; i++) p = p->next;
    Node* t = new Node(x);
    t->next = p->next;
    p->next = t;
}

void deleteBeg(Node* &head) {
    if (head) {
        Node* t = head;
        head = head->next;
        delete t;
    }
}

void deleteEnd(Node* &head) {
    if (!head) return;
    if (!head->next) { delete head; head = NULL; return; }
    Node* p = head;
    while (p->next->next) p = p->next;
    delete p->next;
    p->next = NULL;
}

void deletePos(Node* &head, int pos) {
    if (pos == 0) { deleteBeg(head); return; }
    Node* p = head;
    for (int i = 0; i < pos - 1 && p; i++) p = p->next;
    if (p && p->next) {
        Node* t = p->next;
        p->next = t->next;
        delete t;
    }
}

void print(Node* head) {
    while (head) { cout << head->data << " "; head = head->next; }
    cout << endl;
}

int main() {
    Node* head = NULL;
    insertBeg(head, 10);
    insertEnd(head, 20);
    insertPos(head, 1, 15);
    deletePos(head, 1);
    deleteEnd(head);
    deleteBeg(head);
    print(head);
    return 0;
}
