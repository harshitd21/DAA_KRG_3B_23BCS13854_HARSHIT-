#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int d) { data = d; next = NULL; }
};

class Stack {
    Node* top;
public:
    Stack() { top = NULL; }
    void push(int x) {
        Node* t = new Node(x);
        t->next = top;
        top = t;
    }
    void pop() {
        if (!top) return;
        Node* t = top;
        top = top->next;
        delete t;
    }
    int peek() {
        if (!top) return -1;
        return top->data;
    }
    bool empty() { return top == NULL; }
};

int main() {
    Stack st;
    st.push(10);
    st.push(20);
    st.pop();
    cout << st.peek();
    return 0;
}
