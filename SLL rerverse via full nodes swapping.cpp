#include<iostream>
#include <fstream>
using namespace std;
//sigma code
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
				return;
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
			cout << endl;
		}
		void DisplayReverse_without_tail(){// without tail
			if(head==nullptr){
				cout << "List is Empty." << endl;
				return;
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
			cout << endl;
		}
		void ReverseTheList(){// without tail
			if(head==nullptr){
				cout << "List is Empty." << endl;
				return;
			}
			if(head == tail){// head->next == nullptr
				cout << "List Reversed." << endl;
			}
			int counter = 1;
//			Node* temp_ = head;
//			Node* _temp = head;
//			Node* _curr = head;
			Node* pBehindCurrAtStart;
			Node* currAtStart;
			Node* pBehindCurrAtEnd;
			Node* currAtEnd = head;
			while(currAtEnd->next != nullptr){
				currAtEnd = currAtEnd->next;
				counter++;
			}
			cout << "list size: "<< counter << endl;
			int iteration = 0;
			for(int i=counter;i>0;i--){
				pBehindCurrAtStart = head;
				pBehindCurrAtEnd = head;
				currAtStart = head;
				currAtEnd = head;
				for(int j=1;j<i;j++){
					pBehindCurrAtEnd = currAtEnd;
					currAtEnd = currAtEnd->next;
				}
				for(int j=(counter-i);j>0;j--){
					pBehindCurrAtStart = currAtStart;
					currAtStart = currAtStart->next;
				}
				if(currAtStart == currAtEnd || currAtStart->next == currAtEnd){
					break;
				}
				cout << "behindStartcurr: " << pBehindCurrAtStart->data << endl;
				cout << "Startcurr: " << currAtStart->data << endl;
				cout << "behindEndcurr: " << pBehindCurrAtEnd->data << endl;
				cout << "Endcurr: " << currAtEnd->data << endl;
				tail = currAtStart;
				Node* temp = currAtEnd->next;
				currAtEnd->next = currAtStart->next;
				currAtStart->next = temp;
				pBehindCurrAtEnd->next = currAtStart;
				if (iteration == 0){
					head = currAtEnd;
				}else{
					pBehindCurrAtStart->next = currAtEnd;
				}
				iteration++;
				
				
			}
//			cout << curr_->data << endl;
//			head = curr_;
//			tail = _curr;
//			curr_ = _curr->next;
//			_curr->next = nullptr;
//			temp_->next = _curr;
			
			
//			cout << curr->data;
//			for(int i=counter;i>=1;i--){
//				curr_ = head;
//				for(int m = (counter+1-i);m>0;m--){
//					_temp = _curr;
//					_curr = _curr->next;
//				}
//				for(int j=1;j<i;j++){
//					temp_ = curr_;
//					curr_ = curr_->next;
//				}
//				
//				cout << " <- " << curr->data;
//			}
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
	l.insertAtEnd(1);
	l.insertAtEnd(2);
	l.insertAtEnd(3);
	l.insertAtEnd(4);
	l.insertAtEnd(5);
	l.insertAtEnd(6);
	l.insertAtEnd(7);
	l.insertAtEnd(8);
	l.insertAtEnd(9);
//	l.Display(); // 9 -> 11
//	l.DisplayReverse_without_tail(); // 11 <- 9
	l.ReverseTheList();
	l.Display();
    //---------------------------------------------------------------
    return 0;
}