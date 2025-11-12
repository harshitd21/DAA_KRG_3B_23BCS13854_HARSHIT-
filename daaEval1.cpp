#include <bits/stdc++.h>
using namespace std;

// Creating Nodes
class Node{
    public:
        int value;
        Node* next;

        Node(int value){
            this->value = value;
            next = nullptr;
        }
};

class CiruclarLinkedList{
    private:
        Node* head;
        
    public:
        
        CiruclarLinkedList(int value){
            head = new Node(value);
            head->next = head;    
        }

        void insertAtFirst(int value){
            Node* newNode = new Node(value);
            if (!head){
                head = new Node(value);
                head->next = head;
            } else {
                Node* mover = head;
                while(mover->next != head){
                    mover = mover->next;
                }
                newNode->next = mover->next;
                mover->next = newNode;
                head = newNode;
            }
        }

        void insertInMiddle(int value){
            Node* newNode = new Node(value);
            if (!head){
                head = new Node(value);
                head->next = head;
            } else {
                Node* mover = head;
                int length = 0;
                int middleIdx;

                while(mover->next != head){
                    length++;
                    mover = mover->next;
                }
                middleIdx = length / 2;
                mover = head;

                for (int i = 0; i < middleIdx; i++){
                    mover = mover->next;
                }

                newNode->next = mover->next;
                mover->next = newNode;
            }
        }

        bool deleteReps(void){

            unordered_map<int,int> mpp;
            if (!head) return false;
            int delCounter = 0;

            Node* mover = head;
            Node* deletedNode;

            while (mover->next->next != head){
                if (++mpp[mover->next->value] == 2){
                    mpp[mover->next->value]--;
                    deletedNode = mover->next;
                    mover->next = mover->next->next;
                    deletedNode->next = nullptr;
                    delCounter++;
                    mover = mover->next;
                }

            }

            if (delCounter == 0) return false;
            return true;
}

        void displayLL(void){
            Node* mover = head;
            while(mover){
                cout << mover->value << " ";
                if (mover->next == head){
                    break;
                }
                mover = mover->next;
            }
        }
};


int main(void){
    CiruclarLinkedList* cll = new CiruclarLinkedList(14);
    cll->displayLL();
    cll->insertAtFirst(1);
    cll->insertAtFirst(2);
    cll->insertAtFirst(3);
    cll->insertAtFirst(4);
    cll->insertAtFirst(4);

    cout << endl << endl;
    cll->displayLL();

    cll->insertInMiddle(7);
    cout << endl << endl;
    cll->displayLL();

    cll->insertInMiddle(7);
    cout << endl << endl;
    cll->displayLL();
    
    
    cll->deleteReps();
    cout << endl << endl;
    cll->displayLL();
    return 0;
}

