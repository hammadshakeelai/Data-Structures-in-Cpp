// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};

// LinkedList class
class LinkedList {
private:
    Node* head;
public:
    LinkedList() : head(nullptr) {}
    ~LinkedList();

    void insertAtBeginning(int value) {

    }
    void insertAtEnd(int value);
    void insertAtPosition(int value, int pos);
    bool deleteFromBeginning(int* removedValue = nullptr);
    void display() const;
};
void Lin
// TODO: Implement functions here...

int main() {
    LinkedList list;

    // Step 1: Add 3 passengers at the end
    list.insertAtEnd(101);
    list.insertAtEnd(102);
    list.insertAtEnd(103);
    cout << "Initial Queue after adding passengers:\n";
    list.display();

    // Step 2: Emergency passenger at beginning
    list.insertAtBeginning(999);
    cout << "After adding an emergency passenger at beginning:\n";
    list.display();

    // Step 3: Special booking passenger at position 2
    list.insertAtPosition(555, 2);
    cout << "After inserting special booking passenger at position 2:\n";
    list.display();

    // Step 4: First passenger boards (delete from beginning)
    int removed;
    list.deleteFromBeginning(&removed);
    cout << "After first passenger boards (deletion):\n";
    list.display();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
