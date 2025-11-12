#include <iostream>
using namespace std;

#define SIZE 5

class PriorityQueue {
    int arr[SIZE];
    int n;

public:
    PriorityQueue() {
        n = 0;
    }

    bool isFull() {
        return n == SIZE;
    }

    bool isEmpty() {
        return n == 0;
    }

    void enqueue(int val) {
        if (isFull()) {
            cout << "Queue Overflow\n";
            return;
        }
        arr[n++] = val;
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow\n";
            return;
        }

        int priorityIndex = 0;
        for (int i = 1; i < n; i++) {
            if (arr[i] < arr[priorityIndex]) {
                priorityIndex = i;
            }
        }

        cout << "Deleted: " << arr[priorityIndex] << "\n";

        for (int i = priorityIndex; i < n - 1; i++) {
            arr[i] = arr[i + 1];
        }
        n--;
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        cout << "Queue elements: ";
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
};

int main() {
    PriorityQueue pq;

    pq.enqueue(30);
    pq.enqueue(10);
    pq.enqueue(20);
    pq.enqueue(50);
    pq.enqueue(40);

    pq.display();

    pq.dequeue();  // removes 10 (highest priority = smallest number)
    pq.display();

    pq.dequeue();  // removes 20
    pq.display();

    return 0;
}
