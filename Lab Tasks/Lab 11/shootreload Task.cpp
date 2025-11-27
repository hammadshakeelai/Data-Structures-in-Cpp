#include<iostream>
#include <chrono>
#include <thread>
using namespace std;
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
		bool isFull() {
			if (capacity == currentSize){
				return true;
			}
			return false;
		}
		void reload(int &a,int &b) {// not of queue
			while(!isFull()){
				this_thread::sleep_for(chrono::microseconds(20000));
				enqueue(0);
				cout << b++ << ": ";
				cout << "Magazine Reloaded.\n";
				a--;
			}
		}
		void shoot() {
			this_thread::sleep_for(chrono::microseconds(20000));
			dequeue();
			cout << "Bullet Shot.\n";
		}
};
int main() {
	int bullets = 100;
	Queue *magazine = new Queue(20);
	int i = 0;
	while(bullets > 0){
		
		magazine->reload(bullets,i);
		cout << i++ << ": ";
		magazine->shoot();
		
	}
	cout << "Bullets have ran out.\n";
	return 0;

}