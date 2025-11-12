#include <bits/stdc++.h>
using namespace std;

class Stack {
    int arr[100], top, size;
public:
    Stack(int s) { size = s; top = -1; }
    void push(int x) {
        if (top == size - 1) return;
        arr[++top] = x;
    }
    void pop() {
        if (top == -1) return;
        top--;
    }
    int peek() {
        if (top == -1) return -1;
        return arr[top];
    }
    bool empty() { return top == -1; }
};

int main() {
    Stack st(5);
    st.push(10);
    st.push(20);
    st.pop();
    cout << st.peek();
    return 0;
}
