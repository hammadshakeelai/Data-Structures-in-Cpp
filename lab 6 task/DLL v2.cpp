#include<iostream>
#include <fstream>
using namespace std;
class Node {
	public:
		string ip;
		Node* next;
		Node* prev;
		Node(string iP) : ip(iP), prev(nullptr), next(nullptr) {}
};
class DoublyLinkedList{
	public:
		Node *head;
		Node *tail;
		DoublyLinkedList(){
			cout << "Constructor called, list initialized." << endl;
			head = nullptr;
			tail = nullptr;
		}
		~DoublyLinkedList(){
			Node* temp = head;
			while(head != nullptr){
				head = head->next;
				delete temp;
				temp = head;
			}
			cout << "Destructor called, memory freed." << endl;
		}
		void Display(){
			Node* curr = head;
			if(head==nullptr){
				cout << "List is Empty." << endl;
				return;
			}
			while(curr != nullptr){
				cout << curr->ip;
				if(curr->next != nullptr){
					cout << " -> ";
				}
				curr = curr->next;
			}
			cout << endl;
		}
		void insertAtTheBeginning(string value){
			Node* newNode = new Node(value);
			if(head != nullptr){
				head->prev = newNode;
			} 
			newNode->next = head;
			
			if(head == nullptr){
				tail = newNode;
			}
			head = newNode;
		}
		void insertAtEnd(string value){
			Node* newNode = new Node(value);
			if(tail == nullptr){
				head = newNode;
				tail = newNode;
				return;
			}
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		void Display_Reverse(){
			Node* curr = tail;
			if(tail==nullptr){
				cout << "List is Empty." << endl;
				return;
			}
			while(curr != nullptr){
				cout << curr->ip;
				if(curr->prev != nullptr){
					cout << " <- ";
				}
				curr = curr->prev;
			}
			cout << endl;
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
	DoublyLinkedList *ipAddressList = new DoublyLinkedList;
	ifstream file("ips.txt");
	string line;
	getline(file, line);
	int counter = 1;
	for(char ch:line){
		if (ch==','){
			counter++;
		}
	}
	string word = "";
	int pointer = 0;
	for(char ch : line){
		if(ch==','){
			if (word != ""){
				ipAddressList->insertAtTheBeginning(word);
				pointer++;
				word="";
			}
		}
		else{
			word = word + ch;
		}
	}
	ipAddressList->insertAtTheBeginning(word);
	ipAddressList->Display();
	ipAddressList->Display_Reverse();
	delete ipAddressList;
	file.close();
    //---------------------------------------------------------------
    return 0;
}