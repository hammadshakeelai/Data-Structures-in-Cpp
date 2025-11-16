#include<iostream>
using namespace std;
class Node {
public:
    int val;
	Node* next;
	Node(int value) : val(value), next(nullptr) {}
};
class LinkedList {
private:
    Node* head;
    int length;
public:
    LinkedList() {
        head = nullptr;
        length = 0;
    }
    ~LinkedList() {
        clear();
    }
    void insert(int val, int pos) {
        if (pos <= 0 || pos > (length + 1)) {
            cout<<"out of bounds"<<endl;
            return;
        }
        Node* temp = new Node(val);
        if (pos == 1) {
            temp->next = head;
            head = temp;
        }
        else {
            Node* cur = head;
            for (int i = 1; i < pos - 1; i++) {
                cur = cur->next;
            }
            temp->next = cur->next;
            cur->next = temp;
        }
        length++;
    }
    void remove(int pos) {
        if (head == nullptr || length == 0) {
            cout << "Empty" << endl;
            return;
        }
        if (pos<1 || pos>length) {
            cout << "invalid position" << endl;
            return;
        }
        Node* cur = head;
        if (pos == 1) {
            head = head->next;
            delete cur;
        }
        else {
            for (int i = 1; i < pos - 1; i++) {
                cur = cur->next;
            }
            Node* temp = cur->next;
            cur->next = temp->next;
            delete temp;
        }
        length--;
    }
    int get(int pos) {
        if (head == nullptr || length == 0) {
            cout << "empty" << endl;
            return NULL;
        }
        if (pos<1 || pos>length) {
            cout << "invalid position" << endl;
            return NULL;
        }
        Node* cur = head;
        for (int i = 1; i < pos; i++) {
            cur = cur->next;
        }
        return cur->val;
    }
    void update(int val, int pos) {
        if (head == nullptr || length == 0) {
            cout << "empty" << endl;
            return;
        }
        if (pos<1 || pos>length) {
            cout << "invalid position" << endl;
            return;
        }
        Node* cur = head;
        for (int i = 1; i < pos; i++) {
            cur = cur->next;
        }
        cur->val = val;
    }
    void clear() {
        while (head != nullptr) {
            remove(1);
        }
    }
    int findPos(int val) {
        if  (length == 0 || head == nullptr) {
            return 0; // List is empty
        }
        Node* cur = head;
        int pos = 1;
        while (cur != nullptr) {
            if (cur->val == val) {
                return pos;
            }
            cur = cur->next;
            pos++;
        }
        return 0; // Value not found
    }
    int findVal(int pos){
        if (pos < 1 || pos > length) {
            cout << "invalid position" << endl;
            return NULL;
        }
        if  (length == 0 || head == nullptr) {
            cout << "empty" << endl;
            return NULL;
        }
        return get(pos);
    }
    bool removeVal(int val){
        int pos = findPos(val);
        if (pos != -1) {
            remove(pos);
            return true;
        }
        return false;
    }
};

int main() {
    LinkedList list;
    list.insert(10, 1);
    list.insert(20, 2);
    list.insert(30, 3);
    cout << "Value at position 2: " << list.findVal(2) << endl;
    list.removeVal(20);
    cout << "Value at position 2 after removal: " << list.findVal(2) << endl;
    return 0;
}