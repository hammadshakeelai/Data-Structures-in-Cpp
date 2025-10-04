#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};

class LinkedList {
	
	private:
		Node* head;

	public:
		LinkedList() : head(nullptr) {}
		~LinkedList(){
			Node* cur = head;
			Node* next;
			while(cur){
				next = cur->next;
				delete cur;
				cur = next;
			}
		}

		void insertAtBeginning(int value) {
			Node* node = new Node(value);
			node->next = head;
			head = node;
		}
		void insertAtEnd(int value){
			Node* node = new Node(value);
			if(head==nullptr){
				head = node;
				return;
			}
			Node* cur = head;
			while(cur->next != nullptr){
				cur = cur->next;
			}
			cur->next = node;
		}
		void insertAtPosition(int value, int pos){
			Node* node = new Node(value);
			if(pos==0){
				node->next = head;
				head = node;
				return;
			}
			Node* cur = head;
			for(int i = 0 ; cur != nullptr && i < (pos - 1) ; i++){
				cur = cur->next;
			}
			if(cur == nullptr){
				cout<<"Position Out Of Bounds.\n...\nInserting At End.\n";
				//insertAtEnd(value);
				cur->next = node;
				return;
			}
			node->next = cur->next;
			cur->next = node;
		}
		bool deleteFromBeginning(int* removedValue = nullptr){
			if(head==nullptr){
				return false;
			}
			Node* temp = head;
			if(removedValue){
				*removedValue = temp->data;
			}
			head = temp->next;
			delete temp;
			return true;
		}
		void display() const{
			Node* cur = head;
			while(cur){
				cout<<cur->data<<" ";
				cur = cur->next;
			}
			cout<<endl;
		}
};
int main() {
    LinkedList list;

    // Step 1: Add 3 passengers at the end
    list.insertAtEnd(101);
    list.insertAtEnd(102);
    list.insertAtEnd(103);
    cout << "Initial Queue after adding passengers:\n";
    list.display();

    // Step 2: Emergency passenger at beginning
    list.insertAtBeginning(999);
    cout << "After adding an emergency passenger at beginning:\n";
    list.display();

    // Step 3: Special booking passenger at position 2
    list.insertAtPosition(555, 2);
    cout << "After inserting special booking passenger at position 2:\n";
    list.display();

    // Step 4: First passenger boards (delete from beginning)
    int removed;
    list.deleteFromBeginning(&removed);
    cout << "After first passenger boards (deletion):\n";
    list.display();
    cout<<"Passenger "<<removed<<" Has Boarded.\n";
    cout<<"Passengers Waiting to be boarded are: \n";
    list.display();

    return 0;
}