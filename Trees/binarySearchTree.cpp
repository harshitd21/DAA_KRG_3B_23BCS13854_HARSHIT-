#include <iostream>
#include <queue>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int d): data(d), left(nullptr), right(nullptr) {}
};

class BST {
    Node* insert(Node* root, int x) {
        if (!root) return new Node(x);
        if (x < root->data) root->left = insert(root->left, x);
        else root->right = insert(root->right, x);
        return root;
    }
    Node* findMin(Node* root) {
        while (root->left) root = root->left;
        return root;
    }
    Node* del(Node* root, int x) {
        if (!root) return root;
        if (x < root->data) root->left = del(root->left, x);
        else if (x > root->data) root->right = del(root->right, x);
        else {
            if (!root->left) { Node* t = root->right; delete root; return t; }
            else if (!root->right) { Node* t = root->left; delete root; return t; }
            Node* t = findMin(root->right);
            root->data = t->data;
            root->right = del(root->right, t->data);
        }
        return root;
    }
    void preorder(Node* root) {
        if (!root) return;
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
    void inorder(Node* root) {
        if (!root) return;
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
    void postorder(Node* root) {
        if (!root) return;
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
    void levelorder(Node* root) {
        if (!root) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* t = q.front(); q.pop();
            cout << t->data << " ";
            if (t->left) q.push(t->left);
            if (t->right) q.push(t->right);
        }
    }
public:
    Node* root;
    BST(): root(nullptr) {}
    void insert(int x) { root = insert(root, x); }
    void del(int x) { root = del(root, x); }
    void preorder() { preorder(root); cout << "\n"; }
    void inorder() { inorder(root); cout << "\n"; }
    void postorder() { postorder(root); cout << "\n"; }
    void levelorder() { levelorder(root); cout << "\n"; }
};

int main() {
    BST b;
    b.insert(5);
    b.insert(3);
    b.insert(7);
    b.insert(1);
    b.insert(6);

    cout << "Preorder: "; b.preorder();
    cout << "Inorder: "; b.inorder();
    cout << "Postorder: "; b.postorder();
    cout << "Levelorder: "; b.levelorder();

    b.del(3);
    cout << "After Deletion (Inorder): "; b.inorder();
}

