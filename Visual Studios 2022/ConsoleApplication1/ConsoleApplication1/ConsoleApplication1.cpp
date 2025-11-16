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
public:
    Node* head;
    Node* tail;
    int length;
public:
    CircularLinkedList() : head(nullptr), tail(nullptr), length(0) {}
    ~CircularLinkedList() {
        clear();
    }

    void insert(int val, int pos) {
        if (pos <= 0 || pos > (length + 1)) {
            cout << "out of bounds" << endl;
            return;
        }
        Node* temp = new Node(val);
        if (length == 0) {
            head = tail = temp;
            temp->next = temp->prev = temp;
        }
        else if (pos == 1) {
            temp->next = head;
            temp->prev = tail;
            head->prev = temp;
            tail->next = temp;
            head = temp;
        }
        else if (pos == length + 1) {
            temp->prev = tail;
            temp->next = head;
            tail->next = temp;
            head->prev = temp;
            tail = temp;
        }
        else {
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
        if (pos < 1 || pos > length) {
            cout << "invalid position" << endl;
            return;
        }
        Node* cur = nullptr;
        if (length == 1) {
            cur = head;
            delete cur;
            head = tail = nullptr;
        }
        else if (pos == 1) {
            cur = head;
            head = head->next;
            head->prev = tail;
            tail->next = head;
            delete cur;
        }
        else if (pos == length) {
            cur = tail;
            tail = tail->prev;
            tail->next = head;
            head->prev = tail;
            delete cur;
        }
        else {
            cur = head;
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
        if (pos < 1 || pos > length) {
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
        if (pos < 1 || pos > length) {
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
        if (head == nullptr || length == 0) {
            head = tail = nullptr;
            length = 0;
            return;
        }
        Node* cur = head->next;
        while (cur != head) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        delete head;
        head = tail = nullptr;
        length = 0;
    }

    int findPos(int val) {
        if (head == nullptr || length == 0) return -1;
        Node* cur = head;
        int pos = 1;
        do {
            if (cur->val == val) return pos;
            cur = cur->next;
            pos++;
        } while (cur != head);
        return -1;
    }

    int findVal(int pos) {
        return get(pos);
    }

    bool removeVal(int val) {
        int pos = findPos(val);
        if (pos == -1) return false;
        remove(pos);
        return true;
    }
    int main() {
        CircularLinekedL
            Node* cur = students.head;
        while (students.length > 1) {
            for (int i = 1; i < k; ++i) {
                cur = cur->next;
            }
            Node* temp = cur;
            cur = cur->next;
            students.removeVal(temp->val);
        }
        if (students.head)
            cout << endl << students.head->val << endl;
        cout << "Enter K-th person to be deleted: ";
        int k;
        cin >> k;
        Node* cur = students.head;
        while (students.head != students.tail) {
            for (int i = 1; i < k - 1; i++) {
                cur = cur->next;
            }
            Node* temp = cur->next;
            cur->next = temp->next;
            //
            if (temp->next->prev)
                temp->next->prev = cur;
            if (temp == students.tail) {
                students.tail = cur;
            }
            if (students.head == temp) {
                students.head = cur->next;
            }
            delete temp;

            cur = cur->next;
            //	students.display();
        }
        cout << endl << students.head->val << endl;
        return 0;
    }