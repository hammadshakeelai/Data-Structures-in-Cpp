#include<iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;
// joesephus problem circular linked list
struct Node {
	int data;
	Node* next;
	Node(int value) : data(value), next(nullptr) {}
};
class CircularSinglyLinkedList {
public:
	Node* head;
	Node* tail;

public:
	CircularSinglyLinkedList() : head(nullptr), tail(nullptr) {}
	~CircularSinglyLinkedList() {
		Node* cur = head;
		Node* temp = nullptr;
		do{
			temp = cur->next;
			delete cur;
			cur = temp;
		}while (cur != head);
	}
	void addAtEnd(int value) {//use tail // tick
		Node* node = new Node(value);
		if (head == nullptr) {
			head = node;
			tail = node;
			node->next = head;
			return;
		}
		tail->next = node;
		tail = node;
		node->next = head;
	}
	bool revoveFromHead() {// tick
		if (head == nullptr) {
			cout << "queue is empty.\n";
			return false;
		}
		Node* temp = head;
		head = temp->next;
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
		}while (cur != head);
		return count;
	}
	bool removePos(int pos) {
		if (head == nullptr) {
			cout << "queue is empty.\n";
			return false;
		}
		if(pos > count() || pos < 1) {
			cout << "Pos out of bounds.\n";
			return false;
		}
		Node* temp = head;
		if (pos == 1) {//start
			
			head = head->next;
			delete temp;
			return true;
		}
		for(int i = 1;i < pos-1;i++) 
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
		delete cur;
		return true;
	}
	void Display() const {// tick
		Node* cur = head;
		cout << "Displaying List:\n";
		if (cur == nullptr) {
			cout << "List is empty.\n";
			return;
		}
		 do{
			cout << cur->data << " -> ";
			cur = cur->next;
		}while (cur != head);
	}
	int josephusProblem(int k) {
		if (head == nullptr || k <= 0) {
			cout << "List is empty or invalid k.\n";
			return -1;
		}
		Node* cur = head;
		Node* prev = tail;
		while (count() > 1) {
			for (int i = 1; i < k; i++) {
				prev = cur;
				cur = cur->next;
			}
			prev->next = cur->next;
			if (cur == head) {
				head = cur->next;
			}
			if (cur == tail) {
				tail = prev;
			}
			delete cur;
			cur = prev->next;
		}
		int survivor = head->data;
		delete head;
		head = nullptr;
		tail = nullptr;
		return survivor;
	}
};
int josephusProblem(int n,int m) {
	CircularSinglyLinkedList list;
	for(int i = 1; i <= n; i++) {
		list.addAtEnd(i);
	}
	if (list.head == nullptr || m <= 0) {
		cout << "List is empty or invalid k.\n";
		return -1;
	}
	Node* cur = list.head;
	while (list.count() > 1) {
		for (int i = 1; i < m - 1; i++) {
			cur = cur->next;
		}
		Node* temp = cur->next;
		cur->next = temp->next;
		if (temp == list.head) {
			list.head = temp->next;
		}
		if (temp == list.tail) {
			list.tail = cur;
		}
		delete temp;
		cur = cur->next;
	}
	return list.head->data;
}
int main() {
	auto start = high_resolution_clock::now();   // start time
	//---------------------------------------------------------------
	CircularSinglyLinkedList list;/*
	list.addAtEnd(1);
	list.addAtEnd(2);
	list.addAtEnd(3);
	list.addAtEnd(4);
	cout << list.josephusProblem(2);*/

	cout << "Josephus Problem Simulation:\n";
	int n; // number of people
	cout << "Enter number of people (n): ";
	cin >> n;
	int m; // step count
	cout << "Enter step count (m): ";
	cin >> m;
	cout << "The position of the last remaining person is: " << josephusProblem(n, m) << endl;
	//---------------------------------------------------------------
	auto end = high_resolution_clock::now();     // end time
	auto duration = duration_cast<milliseconds>(end - start);

	cout << "\nExecution time: " << duration.count() << " ms\n";
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
/*int josephusProblem(int k) {
	if (head == nullptr || k <= 0) {
		cout << "List is empty or invalid k.\n";
		return -1;
	}
	Node* cur = head;
	Node* prev = tail;
	while (count() > 1) {
		for (int i = 1; i < k; i++) {
			prev = cur;
			cur = cur->next;
		}
		prev->next = cur->next;
		if (cur == head) {
			head = cur->next;
		}
		if (cur == tail) {
			tail = prev;
		}
		delete cur;
		cur = prev->next;
	}
	int survivor = head->data;
	delete head;
	head = nullptr;
	tail = nullptr;
	return survivor;
}*/