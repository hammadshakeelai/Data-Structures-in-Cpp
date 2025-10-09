// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//Problem Statement : The "Code-a-Thon" T - Shirt Queue
//Background :
	//You are a volunteer at a university "Code-a-Thon" event.The first 100 participants to arrive get a free, limited - edition T - shirt.To manage this, you need to create a simple console - based application that tracks the queue of students waiting for their T - shirts.
	//The process is dynamic : students arrive and join the queue, and sometimes a student has to leave the queue early if they get a call or forget their ID card.The first person in the queue is served when a T - shirt becomes available.
//The Challenge :
	//Your task is to build a system to manage this queue.The system must handle an unknown number of students.You cannot simply reserve space for 100 students in advance, as you don't know how many will show up at any given moment, and the line will constantly change. The system must be efficient when students join or leave the line.
//System Requirements :
//You need to implement a program that provides the following options to the event organizer :
//1.	Add Student : A new student arrives and joins the end of the queue.The system should ask for the student's name and a unique student ID (an integer).
//2.	Serve Student : The student at the front of the queue receives their T - shirt and is removed from the line.The system should display the name of the student who was served.If the queue is empty, it should report that.
//3.	Student Leaves : A student needs to leave the queue unexpectedly.The organizer must be able to remove a student from any position in the queue by entering their unique student ID.
//4.	Display Queue : Show the current list of all students in the queue, from front to back, along with their student IDs.
//5.	Count Students : Display the total number of students currently waiting in the queue.
//Data to Store for Each Student :
	//•	Student Name(e.g., "Ali Khan")
	//•	Student ID(e.g., 12345)
//Hints for Your Thought Process(Why this isn't a simple array problem):
	//	•	How will you handle the list of students if you don't know the maximum number of people who will join the queue?
	//	•	When a student leaves from the middle of the queue, how would you manage the list without having to shift many other students' data around? Think about what would be the most efficient way to "patch up" the line.
	//	•	The order of students is crucial.The first one to arrive must be the first one to be served.
//	What to Submit :
//Submit your source code files.The program should be a menu - driven console application that allows the user to choose from the functions listed above until they choose to exit.
//
//Sample Console Application :
//
//

//add student at end name and id
//serve student remove from start student name if empty display queue is empty
//student leaves remove by id if id not found display id not found
//display queue from front to back with name and id
//count students
#include<iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

struct Node {
	int id;
	string name;
	Node* next;
	Node(int d, string n) : id(d), name(n), next(nullptr) {}
};
class Queue {
private:
	Node* head;
	Node* tail;

public:
	Queue() : head(nullptr), tail(nullptr) {}
	~Queue() {// tick
		Node* cur = head;
		Node* temp = nullptr;
		while (cur) {
			temp = cur->next;
			delete cur;
			cur = temp;
		}
	}
	void AddStudent(int id, string name) {//use tail // tick
		Node* node = new Node(id, name);
		if (head == nullptr) {
			head = node;
			tail = node;
			return;
		}
		tail->next = node;
		tail = node;
	}
	bool ServeStudent() {// tick
		if (head == nullptr) {
			cout << "queue is empty.\n";
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
	bool RemoveStudentById(int Id) {// tick
		if (head == nullptr) {
			cout << "queue is empty.\n";
			return false;
		}
		Node* temp = head;
		if (head->id == Id) {//start
			
			head = head->next;
			delete temp;
			return true;
		}
		while (temp->next && (temp->next)->id != Id) {
			temp = temp->next;
		}
		if (temp->next == nullptr) {
			cout << "ID not found.\n";
			return false;
		}
		Node* cur = temp->next;
		temp->next = cur->next;
		if (cur == tail) {
			tail = temp;
		}
		delete cur;
		return true;
	}
	void DisplayQueue() const {// tick
		Node* cur = head;
		cout << "Displaying Queue:\n";
		while (cur) {
			cout << cur->name << " : " << cur->id << endl;
			cur = cur->next;
		}
	}
};
int main() {
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
	while (choice < 0 || choice > 5) {
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
		queue.AddStudent(id, name);
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
	case 3: {

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
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
