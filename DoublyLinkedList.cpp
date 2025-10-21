#include<iostream>
using namespace std;


struct Node {
	int data;
	Node* prev;
	Node* next;
	Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};
class DoublyLinkedList {
public:
	Node* head;
	Node* tail;

public:
	DoublyLinkedList() : head(nullptr), tail(nullptr) {}
	~DoublyLinkedList() {
		if (head == nullptr) {
			return;
		}
		Node* cur = head;
		Node* temp = nullptr;
		do{
			temp = cur->next;
			delete cur;
			cur = temp;
		}while (cur != nullptr);
	}
	void addAtEnd(int value) {
		Node* node = new Node(value);
		if (head == nullptr) {
			head = node;
			tail = node;
			//node->prev = node;
			//node->next = head;
			return;
		}
		//head->prev = node;
		node->prev = tail;
		tail->next = node;
		tail = node;
		//node->next = head;
	}
	bool removeFromHead() {
		if (head == nullptr) {
			cout << "queue is empty.\n";
			return false;
		}
		Node* temp = head;
		if (head == tail) {//only one node
			head = tail = nullptr;
			delete temp;
			return true;
		}
		head = temp->next;
		temp->next->prev = nullptr;

		//tail->next = head;
		delete temp;
		return true;
	}
	int count() const {
		int count = 0;
		Node* cur = head;
		if (cur == nullptr) {
			return count;
		}
		do{
			count++;
			cur = cur->next;
		}while (cur !=  nullptr);
		return count;
	}
	bool removePos(int pos) {
		if (head == nullptr) {
			cout << "queue is empty.\n";
			return false;
		}
		if (pos > count() || pos < 1) {
			cout << "Pos out of bounds.\n";
			return false;
		}
		Node* temp = head;
		if (pos == 1) {//start

			head = tail = nullptr;
			delete temp;
			return true;
		}
		for (int i = 1; i < pos - 1; i++)
		{
			/*if (temp->next == nullptr) {
				cout << "Pos out of bounds.\n";
				return false;
			}*/
			temp = temp->next;
		}

		Node* cur = temp->next;
		temp->next = cur->next;
		if (cur == tail) {
			tail = temp;
		}
		if (cur->next != nullptr){
			cur->next->prev = temp;
		}
		delete cur;
		return true;
	}
	void display() const {
		Node* cur = head;
		cout << "Displaying List:\n";
		if (cur == nullptr) {
			cout << "List is empty.\n";
			return;
		}
		 do{
			cout << cur->data << " -> ";
			cur = cur->next;
		}while (cur != nullptr);
		 cout << endl;
	}
	
};

int main() {
	
	DoublyLinkedList list;
	list.addAtEnd(10);
	list.addAtEnd(20);
	list.addAtEnd(30);
	list.addAtEnd(40);

	list.display();

	list.removePos(3);
	list.display();

	list.removeFromHead();
	list.display();

	cout << "Count: " << list.count() << endl;

	return 0;
}
