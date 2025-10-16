#include<iostream>
#include <chrono>
#include <fstream>
using namespace std;
using namespace std::chrono;
// ips.txt
// 192.168.1.10,10.0.0.5,172.16.0.1,203.0.113.5,198.51.100.23,8.8.8.8,8.8.4.4,192.0.2.45,10.10.10.10,172.20.14.2,52.214.10.7,34.102.136.180,185.199.108.153,13.35.66.1,44.240.20.10
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
int numofips(string text){
	int counter = 0;
	for(char ch:text){
		if (ch==','){
			counter++;
		}
	}
	return ++counter;
}
int main(){
	auto start = high_resolution_clock::now();   // start time
	//---------------------------------------------------------------
	ifstream file("ips.txt");
	//<-- open file -->
//	if (!file) { // wrote to test if my file was connected 
//		cerr << "Error opening file." << endl;
//	}
	DoublyLinkedList *ipAddressList = new DoublyLinkedList;
	string line;
	getline(file, line);
//	cout << line;
	string arr[numofips(line)];
	split(line,arr);
	for(string ip : arr){
		ipAddressList->insertAtTheBeginning(ip);
	}
	ipAddressList->Display();
	ipAddressList->Display_Reverse();
	
	delete ipAddressList;
	//<-- close file -->
	file.close();
//	DoublyLinkedList *ipAddressList = new DoublyLinkedList;
//	ipAddressList->Display();
//	string ip;
//	file.get(ch)
//	ipAddressList.insertAtTheBeginning(ip);
    //---------------------------------------------------------------
    auto end = high_resolution_clock::now();     // end time
    auto duration = duration_cast<milliseconds>(end - start);

    cout << "\nExecution time: " << duration.count() << " ms\n";
    return 0;
}