#include <bits/stdc++.h>
using namespace std;

struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    DNode(int d) { data = d; prev = next = NULL; }
};

void insertBeg(DNode* &head, int x) {
    DNode* t = new DNode(x);
    if (head) {
        t->next = head;
        head->prev = t;
    }
    head = t;
}

void insertEnd(DNode* &head, int x) {
    DNode* t = new DNode(x);
    if (!head) { head = t; return; }
    DNode* p = head;
    while (p->next) p = p->next;
    p->next = t;
    t->prev = p;
}

void insertPos(DNode* &head, int pos, int x) {
    if (pos == 0) { insertBeg(head, x); return; }
    DNode* p = head;
    for (int i = 0; i < pos - 1 && p; i++) p = p->next;
    DNode* t = new DNode(x);
    t->next = p->next;
    t->prev = p;
    if (p->next) p->next->prev = t;
    p->next = t;
}

void deleteBeg(DNode* &head) {
    if (!head) return;
    DNode* t = head;
    head = head->next;
    if (head) head->prev = NULL;
    delete t;
}

void deleteEnd(DNode* &head) {
    if (!head) return;
    if (!head->next) { delete head; head = NULL; return; }
    DNode* p = head;
    while (p->next) p = p->next;
    p->prev->next = NULL;
    delete p;
}

void deletePos(DNode* &head, int pos) {
    if (pos == 0) { deleteBeg(head); return; }
    DNode* p = head;
    for (int i = 0; i < pos && p; i++) p = p->next;
    if (!p) return;
    if (p->prev) p->prev->next = p->next;
    if (p->next) p->next->prev = p->prev;
    delete p;
}

void print(DNode* head) {
    while (head) { cout << head->data << " "; head = head->next; }
    cout << endl;
}

int main() {
    DNode* head = NULL;
    insertBeg(head, 10);
    insertEnd(head, 20);
    insertPos(head, 1, 15);
    deletePos(head, 1);
    deleteEnd(head);
    deleteBeg(head);
    print(head);
    return 0;
}
