#include <bits/stdc++.h>
using namespace std;

struct CNode {
    int data;
    CNode* next;
    CNode(int d) { data = d; next = this; }
};

void insertBeg(CNode* &head, int x) {
    CNode* t = new CNode(x);
    if (!head) { head = t; return; }
    CNode* p = head;
    while (p->next != head) p = p->next;
    t->next = head;
    p->next = t;
    head = t;
}

void insertEnd(CNode* &head, int x) {
    CNode* t = new CNode(x);
    if (!head) { head = t; return; }
    CNode* p = head;
    while (p->next != head) p = p->next;
    p->next = t;
    t->next = head;
}

void insertPos(CNode* &head, int pos, int x) {
    if (pos == 0) { insertBeg(head, x); return; }
    CNode* p = head;
    for (int i = 0; i < pos - 1; i++) p = p->next;
    CNode* t = new CNode(x);
    t->next = p->next;
    p->next = t;
}

void deleteBeg(CNode* &head) {
    if (!head) return;
    if (head->next == head) { delete head; head = NULL; return; }
    CNode* p = head;
    while (p->next != head) p = p->next;
    CNode* t = head;
    head = head->next;
    p->next = head;
    delete t;
}

void deleteEnd(CNode* &head) {
    if (!head) return;
    if (head->next == head) { delete head; head = NULL; return; }
    CNode* p = head;
    while (p->next->next != head) p = p->next;
    delete p->next;
    p->next = head;
}

void deletePos(CNode* &head, int pos) {
    if (pos == 0) { deleteBeg(head); return; }
    CNode* p = head;
    for (int i = 0; i < pos - 1; i++) p = p->next;
    CNode* t = p->next;
    p->next = t->next;
    delete t;
}

void print(CNode* head) {
    if (!head) return;
    CNode* p = head;
    do { cout << p->data << " "; p = p->next; } while (p != head);
    cout << endl;
}

int main() {
    CNode* head = NULL;
    insertBeg(head, 10);
    insertEnd(head, 20);
    insertPos(head, 1, 15);
    deletePos(head, 1);
    deleteEnd(head);
    deleteBeg(head);
    print(head);
    return 0;
}
