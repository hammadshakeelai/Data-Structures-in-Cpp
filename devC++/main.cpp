#include<iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

struct Node {
	int id;
	string name;
	Node* next;
	Node(int d,string n) : id(d), name(n), next(nullptr) {}
};
class Queue {
private:
	Node* head;
	Node* tail;
	
public:
	Queue() : head(nullptr) ,tail(nullptr) {}
	~Queue() {// tick
		Node* cur = head;
		Node* temp = nullptr;
		while (cur) {
			temp = cur->next;
			delete cur;
			cur = temp;
		}
	}
	void AddStudent(int id,string name) {//use tail // tick
		Node* node = new Node(id,name);
		if (head == nullptr) {
			head = node;
			tail = node;
			return;
		}
		tail->next = node;
		tail = node
	}
	bool ServeStudent() {
		if (head == nullptr) {
			return false;
		}
		Node* temp = head;
		head = temp->next;
		delete temp;
		return true;
	}
	int CountStudents() const {// tick
		int count = 0;
		Node* cur = head;
		while (cur) {
			count++;
			cur = cur->next;
		}
		return count;
	}
	bool RemoveStudentById(int Id) {
		if (head == nullptr) {
			cout << "Queue is empty, cannot remove student." << endl;
			return false;
		}
		Node* cur = head;
		Node* prev;
		while (cur) {
			if (cur->next == nullptr && cur->id == Id){
				delete cur;
				head = nullptr;
				tail = nullptr;
				return true;
			}
			if (cur->id ==Id) {
				prev->next = cur->next;
				cout << "Student with ID " << Id << " has been removed from the queue." << endl;
				delete cur;
				if (cur == tail){
					tail = prev->next;
				}
				return true;
			}
			prev = cur;
			cur = cur->next;
		}
		cout << "Student with ID " << Id << " not found in the queue." << endl;
		return false;
	}
	void DisplayQueue() const {// tick
		Node* cur = head;
		cout << "Displaying Queue:\n";
		while (cur) {
			cout << cur->name << " : " << cur->id <<endl;
			cur = cur->next;
		}
	}
};
int main(){
	auto start = high_resolution_clock::now();   // start time
	//---------------------------------------------------------------

	Queue queue;
	cout << "===== Code-a-Thon T-Shirt Queue Menu =====" << endl;
	cout << "1. Add Student to Queue" << endl;
	cout << "2. Serve Student from Front" << endl;
	cout << "3. A Student Leaves" << endl;
	cout << "4. Display Queue" << endl;
	cout << "5. Count Students in Queue" << endl;
	cout << "0. Exit" << endl;
	cout << "==========================================" << endl;
	cout << "Enter your choice: ";
	int choice;
	cin >> choice;
	while(choice < 0 || choice > 5) {
		cout << "Invalid choice. Please enter a number between 0 and 5: ";
		cin >> choice;
	}
	switch (choice) 
	{
		case 1:
		{
			string name;
			int id;
			cout << "Enter Student's Name: ";
			cin >> name;
			cout << "Enter Student's ID: ";
			cin >> id;
			//call add student function
			queue.AddStudent(id,name);
			//
			cout << "Student " << name << " with ID " << id << " has been added to the queue." << endl;
			break;
		}
		case 2:
		{
			//call serve student function
			queue.ServeStudent();
			//
			cout << "Serving the student at the front of the queue..." << endl;
			break;
		}
		case 3:{
		
			cout << "Enter Student's ID to remove: ";
			int removeId;
			cin >> removeId;
			//call remove student function
			queue.RemoveStudentById(removeId);
			//
			cout << "Student with ID " << removeId << " has been removed from the queue." << endl;
			break;
		}
		case 4:
		{
			//call display queue function
			queue.DisplayQueue();
			//
			break;
		}
		case 5:
		{
			//call count students function
			cout << "Total students in queue: " << queue.CountStudents() << endl;
			//
			break;
		}
		default:
		{
			cout << "Invalid choice. Please try again." << endl;
			break;
		}
	}

    //---------------------------------------------------------------
    auto end = high_resolution_clock::now();     // end time
    auto duration = duration_cast<milliseconds>(end - start);

    cout << "\nExecution time: " << duration.count() << " ms\n";
    return 0;
}