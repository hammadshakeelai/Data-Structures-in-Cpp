#include<iostream>
#include <fstream>
using namespace std;
class Node {
	public:
		int data;
		Node* next;
		Node(int value) : data(value), next(nullptr) {}
};
class SinglyLinkedList{
	public:
		Node *head;
		Node *tail;
		SinglyLinkedList(){
			cout << "Constructor called, list initialized." << endl;
			head = nullptr;
			tail = nullptr;
		}
		~SinglyLinkedList(){
			Node* temp = head;
			while(head != nullptr){
				head = head->next;
				delete temp;
				temp = head;
			}
			cout << "\nDestructor called, memory freed." << endl;
		}
		void Display(){
			Node* curr = head;
			if(head==nullptr){
				cout << "List is Empty." << endl;
				return;
			}
			while(curr != nullptr){
				cout << curr->data;
				if(curr->next != nullptr){
					cout << " -> ";
				}
				curr = curr->next;
			}
			cout << endl;
		}
		void insertAtTheBeginning(int value){
			Node* newNode = new Node(value);
			newNode->next = head;
			if(head == nullptr){
				tail = newNode;
			}
			head = newNode;
		}
		void insertAtEnd(int value){
			Node* newNode = new Node(value);
			if(tail == nullptr){
				head = newNode;
				tail = newNode;
				return;
			}
			tail->next = newNode;
			tail = newNode;
		}
		void DisplayReverse(){
			if(head==nullptr){
				cout << "List is Empty." << endl;
			}
			int counter = 1;
			Node* curr = head;
			while(curr->next != tail){
				curr = curr->next;
				counter++;
			}
			counter++;
			cout << curr->next->data;
			for(int i=(counter-1);i>=1;i--){
				curr = head;
				for(int j=1;j<i;j++){
					curr = curr->next;
				}
				cout << " <- " << curr->data;
			}
		}
		void DisplayReverse_without_tail(){// without tail
			if(head==nullptr){
				cout << "List is Empty." << endl;
			}
			int counter = 0;
			Node* curr = head;
			while(curr->next != nullptr){
				curr = curr->next;
				counter++;
			}
			cout << curr->data;
			for(int i=counter;i>=1;i--){
				curr = head;
				for(int j=1;j<i;j++){
					curr = curr->next;
				}
				cout << " <- " << curr->data;
			}
		}
};
void split(string text,string array[]) {
	string word = "";
	int pointer = 0;
	for(char ch : text){
		if(ch==','){
			if (word != ""){
				array[pointer] = word;
				pointer++;
				word="";
			}
		}
		else{
			word = word + ch;
		}
	}
	array[pointer] = word;
}
int main(){
	//---------------------------------------------------------------
	SinglyLinkedList l;
	l.insertAtEnd(9);
	l.insertAtEnd(11);
	l.Display();
	l.DisplayReverse_without_tail();
    //---------------------------------------------------------------
    return 0;
}