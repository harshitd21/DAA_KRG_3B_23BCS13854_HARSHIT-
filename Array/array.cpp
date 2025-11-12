#include <bits/stdc++.h>
using namespace std;

void insertAtPos(int arr[], int &n, int pos, int val) {
    for (int i = n; i > pos; i--) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = val;
    n++;
}

void deleteBeg(int arr[], int &n) {
    for (int i = 0; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    n--;
}

void deleteEnd(int &n) {
    n--;
}

void deleteAtPos(int arr[], int &n, int pos) {
    for (int i = pos; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    n--;
}

int main() {
    int arr[100] = {1, 2, 3, 4, 5};
    int n = 5;

    insertAtPos(arr, n, 2, 99);
    deleteBeg(arr, n);
    deleteEnd(n);
    deleteAtPos(arr, n, 1);

    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    return 0;
}
