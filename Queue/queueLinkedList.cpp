#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int d) { data = d; next = NULL; }
};

class Queue {
    Node* front;
    Node* rear;
public:
    Queue() { front = rear = NULL; }
    void enqueue(int x) {
        Node* t = new Node(x);
        if (!rear) { front = rear = t; return; }
        rear->next = t;
        rear = t;
    }
    void dequeue() {
        if (!front) return;
        Node* t = front;
        front = front->next;
        if (!front) rear = NULL;
        delete t;
    }
    int peek() {
        if (!front) return -1;
        return front->data;
    }
    bool empty() { return front == NULL; }
};

int main() {
    Queue q;
    q.enqueue(10);
    q.enqueue(20);
    q.dequeue();
    cout << q.peek();
    return 0;
}
