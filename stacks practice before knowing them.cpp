#include<iostream>
#include <fstream>
using namespace std;
class Node {
public:
	int data;
	Node* next;
	Node(int value) : data(value), next(nullptr) {}
};
class SinglyLinkedList {
public:
	Node* head;
	SinglyLinkedList() {
		cout << "Constructor called, list initialized." << endl;
		head = nullptr;
	}
	~SinglyLinkedList() {
		Node* temp = head;
		while (head != nullptr) {
			head = head->next;
			delete temp;
			temp = head;
		}
		cout << "\nDestructor called, memory freed." << endl;
	}
	void pop() {
		if (head == nullptr) {
			cout << "List is empty, nothing to pop." << endl;
			return;
		}
		Node* temp = head;
		head = head->next;
		delete temp;
	}
	void peak () {
		if (head != nullptr) {
			cout << "Head: " << head->data << endl;
		}
		else {
			cout << "List is empty, no head." << endl;
		}
	}
	void Display() {
		Node* curr = head;
		if (head == nullptr) {
			cout << "List is Empty." << endl;
			return;
		}
		while (curr != nullptr) {
			cout << curr->data;
			if (curr->next != nullptr) {
				cout << " -> ";
			}
			curr = curr->next;
		}
		cout << endl;
	}
	void insertAtTheBeginning(int value) {
		Node* newNode = new Node(value);
		newNode->next = head;
		head = newNode;
	}
	void DisplayReverse_without_tail() {
		if (head == nullptr) {
			cout << "List is Empty." << endl;
		}
		int counter = 0;
		Node* curr = head;
		while (curr->next != nullptr) {
			curr = curr->next;
			counter++;
		}
		cout << curr->data;
		for (int i = counter; i >= 1; i--) {
			curr = head;
			for (int j = 1; j < i; j++) {
				curr = curr->next;
			}
			cout << " <- " << curr->data;
		}
	}
};
class stack_d {
	public:
		SinglyLinkedList list;
		void add(int value) {
			list.insertAtTheBeginning(value);
		}
		void remove() {
			list.pop();
		}
		void peak() {
			list.peak();
		}
		void displayfullstack() {
			list.Display();
		}
};
class stack_f {
	private:
		int* arr;
		int size;
		int length = 0;
	public:
		stack_f(int s) {
			arr = new int[s];
			size = s;
		}
		~stack_f() {
			delete[] arr;
		}
		void add(int value) {
			if (length < size) {
				arr[length] = value;
				length++;
			}
			else {
				cout << "Stack Overflow" << endl;
			}
		}
		void remove() {
			if (length > 0) {
				length--;
			}
			else {
				cout << "Stack Underflow" << endl;
			}
		}
		void peak() {
			if (length > 0) {
				cout << "Top element: " << arr[length - 1] << endl;
			}
			else {
				cout << "Stack is empty" << endl;
			}
		}
		void displayfullstack() {
			if (length == 0) {
				cout << "Stack is empty" << endl;
				return;
			}
			/*for (int i = length - 1; i >= 0; i--) {
				cout << arr[i];
				if (i != 0) {
					cout << " -> ";
				}
			}*/
			for(int i = 0; i < length; i++) {
				cout << arr[i];
				if (i != length - 1) {
					cout << " -> ";
				}
			}
			cout << endl;
		}

};;
int main() {
	//---------------------------------------------------------------
	
	//---------------------------------------------------------------
	return 0;
}