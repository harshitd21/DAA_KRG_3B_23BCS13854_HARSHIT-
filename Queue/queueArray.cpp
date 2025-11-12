#include <bits/stdc++.h>
using namespace std;

class Queue {
    int arr[100], front, rear, size;
public:
    Queue(int s) { size = s; front = 0; rear = -1; }
    void enqueue(int x) {
        if (rear == size - 1) return;
        arr[++rear] = x;
    }
    void dequeue() {
        if (front > rear) return;
        front++;
    }
    int peek() {
        if (front > rear) return -1;
        return arr[front];
    }
    bool empty() { return front > rear; }
};

int main() {
    Queue q(5);
    q.enqueue(10);
    q.enqueue(20);
    q.dequeue();
    cout << q.peek();
    return 0;
}
