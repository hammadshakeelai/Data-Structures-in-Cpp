#include<iostream>
using namespace std;
struct Node {
    int data;
    Node* next;
    Node(int argData) {
        data = argData;
        next = nullptr;
    }
};
class LinkedList {
private:
    Node* head;
public:
    LinkedList() {
        head = nullptr;
    }
    ~LinkedList() {
        while (head != nullptr) {
            deleteFromBeginning();
        }
        /*
        Node* cur = head;
        Node *temp =nullptr;
        while(cur->next != nullptr){
            temp = cur->next;
            delete cur;
            cur = temp;
        }
        */
    }
    void insertAtBeginning(int value) {
        Node* temp = new Node(value);
        temp->next = head;
        head = temp;
    }
    void insertAtEnd(int value) {
        Node* temp = new Node(value);
        if (head == nullptr) {
            head = temp;
            return;
        }
        Node* cur = head;
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = temp;
	}
    void insertAtPosition(int value, int position) {
        if (position == 0) {
            insertAtBeginning(value);
            return;
        }
        Node* temp = new Node(value);
        Node* cur = head;
        for (int i = 0; i < position - 1 && cur != nullptr; i++) {
            cur = cur->next;
        }
        if (cur == nullptr) {
			cout << "Position out of bounds. Inserting at the end." << endl;
			insertAtEnd(value);
            return;
        }
        temp->next = cur->next;
        cur->next = temp;
	}
    bool deleteFromBeginning(int *removed = nullptr) {
        if (head == nullptr) {
            cout << "List is empty. Cannot delete." << endl;
            return false;
        }
        Node* temp = head;
        if(removed != nullptr) {
            *removed = head->data;
		}
        head = head->next;
        delete temp;
        return true;
    }
    void deleteFromEnd() {
        if (head == nullptr) {
            cout << "List is empty. Cannot delete." << endl;
            return;
        }
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return;
        }
        Node* cur = head;
        while (cur->next->next != nullptr) {
            cur = cur->next;
        }
        delete cur->next;
        cur->next = nullptr;
    }
    void display() {
        Node* cur = head;
        while (cur != nullptr) {
            cout << cur->data << " -> ";
            cur = cur->next;
        }
        cout << "nullptr" << endl;
	}

};
int main() {
    
    return 0;
}