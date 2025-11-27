#include<iostream>
using namespace std;
class Node {
	public:
		int data;
		Node* next;
		Node(int val) {
			data = val;
			next = nullptr;
		}
};
class Stack {
	public:
		Node* top;
		Stack(){
			top = nullptr;
		}
		~Stack() {
			while(top != nullptr){
				pop();
			}
		}
		void push(int val) {
			Node* node = new Node(val);
			node->next = top;
			top = node;
		}
		int pop() {
			if (top == nullptr) {
				cout << "Stack Underflow" << endl;
				return -1;
			}
			Node* temp = top;
			int poppedValue = top->data;
			top = top->next;
			delete temp;
			return poppedValue;
		}
		int peek() {
			if (top == nullptr) {
				cout << "Stack Underflow" << endl;
				return -1;
			}
			return top->data;
		}
		void display() {
			Node* curr = top;
			while (curr != nullptr) {
				cout << curr->data << "  ";
			}
			cout << endl;
		}
};
class Queue {
	private:
		int* arr;
		int capacity;//max size
		int frontIdx;
		int rearIdx;
		int currentSize;
		void resize() {
			int newCapacity = capacity * 2;
			int* newArr = new int[newCapacity];
			for (int i = 0; i < currentSize; i++) {
				newArr[i] = arr[(frontIdx + i) % capacity];
			}
			delete[] arr;
			arr = newArr;
			capacity = newCapacity;
			frontIdx = 0;
			rearIdx = currentSize;
		}
	public:
		Queue(int initialCapacity = 4) {
			capacity = initialCapacity;
			arr = new int[capacity];
			frontIdx = 0;
			rearIdx = 0;
			currentSize = 0;
		}
		~Queue() {
			delete[] arr;
		}
		bool isEmpty() const {
			if (currentSize == 0) {
				return true;
			}
			if (currentSize != 0) { // not important
				return false;
			}
		}
		int size() const {
			return currentSize;
		}
		void enqueue(int value) {
			if (currentSize == capacity) {
				resize();
			}
			arr[rearIdx] = value;
			rearIdx = (rearIdx + 1) % capacity;
			currentSize++;
		}
		void dequeue() {
			if (isEmpty()) {
				cout << "Queue Underflow! Cannot dequeue from an empty queue.\n";
				return;
			}
			frontIdx = (frontIdx + 1) % capacity;
			currentSize--;
		}
		int front() const {
			if (isEmpty()) {
				cout << "Queue is empty. No front element.\n";
				return -1;
			}
			return arr[frontIdx];
		}
		void print() const {
			cout << "Queue elements: ";
			for(int i = 0;i < currentSize;i++) {
				int index = (frontIdx + i) % capacity;
				cout << arr[index] << " ";
			}
			cout << "\n";
		}
};
int main() {
	Queue q;
	cout << "Enqueue 10, 20, 30, 40\n";
	q.enqueue(10);
	q.enqueue(20);
	q.enqueue(30);
	q.enqueue(40);
	q.print();

	cout << "Front elemet: " << q.front() << "\n";

	cout << "Dequeue two elements\n";
	q.dequeue();
	q.dequeue();
	q.print();
	cout << "Front element now: " << q.front() << "\n";
	cout << "Enqueue 50, 60, 70 (this will cause resize internally)\n";
	q.enqueue(50);
	q.enqueue(60);
	q.enqueue(70);
	q.print();

	cout << "Dequeue all elements:\n";
	while(!q.isEmpty()) {
		cout << "Front: " << q.front() << " -> dequeued\n";
		q.dequeue();
	}
	q.dequeue();
	return 0;

}