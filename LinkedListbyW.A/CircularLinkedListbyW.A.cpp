#include<iostream>
using namespace std;
class Node {
public:
    int val;
    Node* next;
    Node* prev;
    Node(int value) : val(value), prev(nullptr), next(nullptr) {}
};
class CircularLinkedList {
private:
    Node* head;
    Node* tail;
    int length;
public:
    CircularLinkedList() {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }
    ~CircularLinkedList() {
        clear();
    }
    void insert(int val, int pos) {
        if (pos <= 0 || pos > (length + 1)) {
            cout<<"out of bounds"<<endl;
            return;
        }
        Node* temp = new Node(val);
        if (length == 0) {
            head = tail = temp;
        } else if (pos == 1) {
            temp->next = head;
            head->prev = temp;
            head = temp;
        } else if (pos == length + 1) {
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        } else {
            Node* cur = head;
            for (int i = 1; i < pos - 1; i++) {
                cur = cur->next;
            }
            temp->next = cur->next;
            temp->prev = cur;
            cur->next->prev = temp;
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
        if (length == 1) {
            delete head;
            head = tail = nullptr;
        } else if (pos == 1) {
            Node* cur = head;
            head = head->next;
            head->prev = nullptr;
            delete cur;
        } else if (pos == length) {
            Node* cur = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete cur;
        } else {
            Node* cur = head;
            for (int i = 1; i < pos; i++) {
                cur = cur->next;
            }
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
            delete cur;
        }
        length--;
    }
    int get(int pos) {
        if (head == nullptr || length == 0) {
            cout << "empty" << endl;
            return -1;
        }
        if (pos<1 || pos>length) {
            cout << "invalid position" << endl;
            return -1;
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
        Node* cur = head;
        while (cur != nullptr) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        head = tail = nullptr;
        length = 0;
    }
    int findPos(int val) {
        Node* cur = head;
        int pos = 1;
        while (cur != nullptr) {
            if (cur->val == val) return pos;
            cur = cur->next;
            pos++;
        }
        return -1;
    }
    int findVal(int pos){
        return get(pos);
    }
    bool removeVal(int val){
        int pos = findPos(val);
        if (pos == -1) return false;
        remove(pos);
        return true;
    }

};

int main() {
    
    return 0;
}