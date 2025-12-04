#include<iostream>
using namespace std;
class Node {
	public:
		int data;
		Node* right;
		Node* left;
		Node() {
			left = nullptr;
			right = nullptr;
		}
};
/*
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
*/
Node* getNewNode(int data) {
	Node* newNode = new Node();
	newNode->data = data;
	return newNode;
}
Node* insert(Node* root, int data)
int main() {
	
	return 0;

}
/*C++ Stack Practice Problems
Here are several scenario-based problems designed to help you practice and understand the various uses of the Stack data structure.

🏛️ Problem 1: The Balanced Brackets Checker
Scenario
You are building a linter for a new code editor. The most fundamental feature is checking for valid syntax. The first step is to ensure that all brackets (or parentheses) are balanced. This means every opening bracket has a matching closing bracket in the correct order.

Task
Write a C++ function bool areBracketsBalanced(string expression) that takes a string and returns true if all brackets are balanced, and false otherwise.

Your function must handle three types of brackets:

Parentheses: ( and )
Square Brackets: [ and ]
Curly Braces: { and }
Logic Hint
Create a stack that can hold characters (char).
Iterate through the expression string, character by character.
If you encounter an opening bracket ((, [, or {), push it onto the stack.
If you encounter a closing bracket (), ], or }):
Check if the stack is empty. If it is, you found a closing bracket with no opener. Return false.
If it's not empty, pop the top element.
Check if the popped element is the matching opener for the current closing bracket.
If ) is found, the popped element must be (.
If ] is found, the popped element must be [.
If } is found, the popped element must be {.
If they do not match, return false.
After the loop finishes, check if the stack is empty. If it is, all brackets were matched. Return true. If it's not empty, it means there are leftover opening brackets. Return false.
Test Cases
"{[()]}" 
→
 true
"{[(])}" 
→
 false (Mismatched: ] found, ( expected)
"{{[[(())]]}}" 
→
 true
"{" 
→
 false (Leftover opener)
")" 
→
 false (Closing bracket with no opener)
🎶 Problem 2: The Music Player 'Previous Track' Button
Scenario
You are programming the logic for a music player (like Spotify or Apple Music). The player needs a "history" feature. When a user skips to the next song, the previous song should be saved in a "history" list. When the user hits the "Back" button, it should play the last song they were listening to.

This sounds just like a stack!

Task
Design a MusicPlayer class.

It should have a string currentTrack.
It needs a playTrack(string newTrack) method. When this is called, it should:
Push the currentTrack onto a "history" stack.
Set currentTrack to the newTrack.
It needs a playPrevious() method. When this is called, it should:
Check if the "history" stack is empty. If so, print "No previous tracks."
If not empty, pop the top track from the history stack and set it as the currentTrack.
Logic Hint
You will need a stack that can store strings. (e.g., std::stack<string> or a custom stack that holds string data).

Test Case
player.playTrack("Bohemian Rhapsody")
(History stack is empty, currentTrack becomes "Bohemian Rhapsody")
player.playTrack("Stairway to Heaven")
(Pushes "Bohemian Rhapsody" onto the stack, currentTrack becomes "Stairway to Heaven")
player.playTrack("Hotel California")
(Pushes "Stairway to Heaven" onto the stack, currentTrack becomes "Hotel California")
player.playPrevious()
(Pops "Stairway to Heaven". currentTrack is now "Stairway to Heaven".)
player.playPrevious()
(Pops "Bohemian Rhapsody". currentTrack is now "Bohemian Rhapsody".)
player.playPrevious()
(Stack is empty. Prints "No previous tracks.")
🧮 Problem 3: The Reverse Polish Notation (RPN) Calculator
Scenario
You are asked to build a special calculator that doesn't need parentheses. It uses Postfix Notation, also known as Reverse Polish Notation (RPN). In RPN, the operator comes after the numbers.

2 + 3 becomes 2 3 +
(2 + 3) * 4 becomes 2 3 + 4 *
Task
Write a function int evaluatePostfix(string expression) that takes a postfix expression string and returns the integer result.

You can assume the expression has single-digit numbers (0-9) and the operators +, -, *, /.
The numbers and operators will be separated by spaces (e.g., "5 3 + 2 *").
Logic Hint
Create a stack that can hold ints.
Split the input string by spaces.
Iterate through each part of the expression.
If the part is a number: push it onto the stack.
If the part is an operator (+, -, *, /):
Pop the top value (call it a).
Pop the next top value (call it b).
Perform the operation: b operator a (Order matters for - and /!)
Push the result back onto the stack.
After the loop, the stack should contain exactly one number: the final result. Return it.
Test Cases
"5 3 +" 
→
 (Pop 3, Pop 5, Push 5+3) 
→
 8
"5 3 + 2 *" 
→
 (Push 5, Push 3, Pop 3, Pop 5, Push 8, Push 2, Pop 2, Pop 8, Push 8*2) 
→
 16
"7 4 - 3 *" 
→
 (Push 7, Push 4, Pop 4, Pop 7, Push 3, Push 3, Pop 3, Pop 3, Push 3*3) 
→
 9
"8 4 /" 
→
 (Pop 4, Pop 8, Push 8/4) 
→
 2*/