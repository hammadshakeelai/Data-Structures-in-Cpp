#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

void bubbleSort(int arr[], int n) {
    bool swapped;
    for(int i = 0; i < n - 1; i++) {
        swapped = false;
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if(!swapped)//swapped === false
            break;
    }
}

int main() {
    ifstream fin("numbers.txt");
    if (!fin) {
        cout << "Error in opening file\n";
        return 0;
    }

    string line, token;
    getline(fin, line);
    fin.close();

    int count = 1;
    for (char c : line) {
        if (c == ',')
            count++;
    }

    int* arr = new int[count];
    int n = 0;
    stringstream ss(line);
    while (getline(ss, token, ',')) {
        arr[n++] = stoi(token);
    }

    auto start = high_resolution_clock::now();
    bubbleSort(arr, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Sorted Array: ";
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << "\nTime taken by bubble sort: "
         << duration.count() << " milliseconds\n";

    delete[] arr;
    return 0;
}#include <iostream>
#include <string>
#include <limits>
using namespace std;

// =========================================================
// 1. NODE STRUCTURE
// =========================================================
struct TimeCapsule {
    int year;
    string eventName;
    TimeCapsule* left;
    TimeCapsule* right;

    TimeCapsule(int y, string n) : year(y), eventName(n), left(nullptr), right(nullptr) {}
};

// =========================================================
// 2. BST CLASS
// =========================================================
class TimeTree {
private:
    TimeCapsule* root;

    // =========================================================
    // (1) INSERT HELPER  – Implements BST insertion
    // =========================================================
    TimeCapsule* insertHelper(TimeCapsule* node, int year, string name) {
        if (node == nullptr)
            return new TimeCapsule(year, name);     // Create new node

        if (year < node->year)
            node->left = insertHelper(node->left, year, name);   // Go left
        else if (year > node->year)
            node->right = insertHelper(node->right, year, name); // Go right

        return node; // Return unchanged root
    }

    // =========================================================
    // (2) SEARCH HELPER – Standard BST search
    // =========================================================
    TimeCapsule* searchHelper(TimeCapsule* node, int year) {
        if (!node) return nullptr;
        if (year == node->year) return node;
        if (year < node->year) return searchHelper(node->left, year);
        return searchHelper(node->right, year);
    }

    // =========================================================
    // (3) FIND MIN (Inorder Successor)
    // =========================================================
    TimeCapsule* findMin(TimeCapsule* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

    // =========================================================
    // (4) DELETE HELPER – Handles all 3 delete cases
    // =========================================================
    TimeCapsule* deleteHelper(TimeCapsule* node, int year) {
        if (!node) return nullptr;

        if (year < node->year)
            node->left = deleteHelper(node->left, year);
        else if (year > node->year)
            node->right = deleteHelper(node->right, year);
        else {
            // Case 1: Leaf
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            // Case 2: One child
            else if (!node->left) {
                TimeCapsule* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                TimeCapsule* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: Two children
            TimeCapsule* successor = findMin(node->right);
            node->year = successor->year;
            node->eventName = successor->eventName;
            node->right = deleteHelper(node->right, successor->year);
        }
        return node;
    }

    // =========================================================
    // (5) INORDER TRAVERSAL for REPORT
    // =========================================================
    void inorder(TimeCapsule* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->year << " → " << node->eventName << endl;
        inorder(node->right);
    }

    // =========================================================
    // Destroy the entire tree (Destructor helper)
    // =========================================================
    void destroyTree(TimeCapsule* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:

    TimeTree() { root = nullptr; }
    ~TimeTree() { destroyTree(root); }

    // =========================================================
    // (6) INJECT – Public insert using helper
    // =========================================================
    void inject(int year, string name) {
        cout << "> System: Injecting " << year << "... ";
        root = insertHelper(root, year, name);
        cout << "Timeline stable." << endl;
    }

    // =========================================================
    // (7) PARADOX – Public delete using helper
    // =========================================================
    void resolveParadox(int year) {
        cout << "> Alert: Paradox detected at " << year << "!" << endl;

        if (!searchHelper(root, year)) {
            cout << "> System: Year not found. No paradox removed." << endl;
            return;
        }

        root = deleteHelper(root, year);
        cout << "> System: Paradox resolved. Year removed." << endl;
    }

    // =========================================================
    // (8) SEARCH – Uses searchHelper
    // =========================================================
    void search(int year) {
        cout << "> Query: Searching for " << year << "..." << endl;

        TimeCapsule* result = searchHelper(root, year);
        if (result)
            cout << "> Result: Event Found! [" << result->year << ": " << result->eventName << "]" << endl;
        else
            cout << "> Result: Year not found." << endl;
    }

    // =========================================================
    // (9) REPORT – Uses inorder() to print ASC years
    // =========================================================
    void report() {
        cout << "> COMMAND: CHRONOLOGICAL REPORT" << endl;
        cout << "-------------------------------" << endl;
        inorder(root);
        cout << "-------------------------------" << endl;
    }

    // =========================================================
    // (10) TIME SPAN – Bonus Feature
    // =========================================================
    void calculateTimeSpan() {
        if (!root) {
            cout << "> TimeSpan: Tree empty." << endl;
            return;
        }

        TimeCapsule* minNode = root;
        while (minNode->left) minNode = minNode->left;

        TimeCapsule* maxNode = root;
        while (maxNode->right) maxNode = maxNode->right;

        cout << "> TimeSpan: " << (maxNode->year - minNode->year) << " years." << endl;
    }
};

// =========================================================
// 3. MAIN PROGRAM (unchanged)
// =========================================================
int main() {
    TimeTree chronos;
    string command;
    int year;
    string eventName;

    cout << "--- CHRONOS TIME STABILIZER V1.0 ---" << endl;
    cout << "Waiting for Time Stream Inputs..." << endl << endl;

    while (cin >> command) {
        if (command == "INJECT") {
            cin >> year;
            getline(cin >> ws, eventName);
            chronos.inject(year, eventName);
        }
        else if (command == "PARADOX") {
            cin >> year;
            chronos.resolveParadox(year);
        }
        else if (command == "SEARCH") {
            cin >> year;
            chronos.search(year);
        }
        else if (command == "REPORT") {
            chronos.report();
        }
        else if (command == "EXIT") {
            break;
        }
        else {
            cout << "> Unknown Command." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << endl;
    }

    return 0;
}#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
	int tp,pp,id;
	cout<<"Enter the total number of participant ";
	cin>>tp;

	int *attendance;
	attendance=(int*)calloc(tp,sizeof(int));

	cout<<"Enter the number of present participant ";
	cin>>pp;

	for (int i=0; i<pp; i++)
	{
		cout<<"Enter the id of prsent participant ";
		cin>>id;

		if (id>=1 && id<=tp)
		{
			attendance[id-1]=1;
		}
		else
		{
			cout<<"Invalid id: This id does not exist"<<endl;
		}
	}
	for(int i=0; i<tp; i++)
	{
		if (attendance[i] == 1)
		{
			cout<<"Participant id no "<<i+1<<" : Present"<<endl;
		}
		else
		{
			cout<<"Participant id no: "<<i+1<<" : Absent"<<endl;
		}
	}
	attendance=nullptr;
	return 0;

}#include <iostream>
using namespace std;

class Student {
public:
    string name;
    int ID;
    Student* next;

    Student(string n, int id) {
        name = n;
        ID = id;
        next = nullptr;
    }
};

class Code_of_Thon {
private:
    Student* head;

public:
    Code_of_Thon() : head(nullptr) {}

    void Add_Student(string n, int id) {
        Student* student = new Student(n, id);
        if (head == nullptr) {
            head = student;
            return;
        }
        Student* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = student;
    }

    bool Serve_Student(string* removedName = nullptr, int* removedID = nullptr) {
        if (head == nullptr) return false;
        Student* temp = head;
        if (removedName) *removedName = temp->name;
        if (removedID) *removedID = temp->ID;
        head = head->next;
        delete temp;
        return true;
    }

    bool Student_Leaves(int position, string* removedName = nullptr, int* removedID = nullptr) {
    if (head == nullptr) {
        cout << "Queue is empty, nothing to delete." << endl;
        return false;
    }
    if (position < 0) {
        cout << "Invalid position." << endl;
        return false;
    }
   
    Student* temp = head;
    for (int i = 0; temp != nullptr && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == nullptr || temp->next == nullptr) {
        cout << "Position is out of bounds." << endl;
        return false;
    }
    Student* nodeToDelete = temp->next;
    if (removedName) *removedName = nodeToDelete->name;
    if (removedID) *removedID = nodeToDelete->ID;
    temp->next = nodeToDelete->next;
    delete nodeToDelete;
    return true;
}


    int Count_Student() {
        int count = 0;
        Student* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void Display_Queue() {
        Student* temp = head;
        while (temp != nullptr) {
            cout << temp->name << "(" << temp->ID << ") -> ";
            temp = temp->next;
        }
        cout << "Null" << endl;
    }
};

int main() {
    Code_of_Thon queue;
    int id;
	int pos;
    string name;
    int choice;

    do {
        cout << "\n===== Code a Thon =====\n";
        cout << "1. Add student to queue\n";
        cout << "2. Serve student from beginning\n";
        cout << "3. A student leaves \n";
        cout << "4. Display queue\n";
        cout << "5. Count students in queue\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Student's name: ";
                cin >> name;
                cout << "Enter Student's ID: ";
                cin >> id;
                queue.Add_Student(name, id);
                cout << name << " has been added to the queue." << endl;
                break;

            case 2: {
                string removedName;
                int removedID;
                if (queue.Serve_Student(&removedName, &removedID)) {
                    cout << removedName << " (ID: " << removedID << ") has been served." << endl;
                } else {
                    cout << "Queue is empty, no student to serve." << endl;
                }
                break;
            }

            case 3: {
                cout << "Enter Student's position to leave (0-based index): ";
                cin >> pos;
                string removedName;
                int removedID;
                if (queue.Student_Leaves(pos, &removedName, &removedID)) {
                    cout << removedName << " (ID: " << removedID << ") has left the queue." << endl;
                }
                break;
}


            case 4:
                cout << "Current queue: ";
                queue.Display_Queue();
                break;

            case 5:
                cout << "Number of students in queue: " << queue.Count_Student() << endl;
                break;

            case 6:
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid choice, please try again." << endl;
        }

    } while (choice != 6);

    return 0;
}#include<iostream>
using namespace std;
int main(){
	int cap=250, lat=200, esp=300;
	int*ptrcap=&cap;
	int*ptrlat=&lat;
	int*ptresp=&esp;
	int quantcap=0,quantlat=0,quantesp=0;
	int*ptrcapq=&quantcap;
	int*ptrlatq=&quantlat;
	int*ptrespq=&quantesp;
	cout<<("enter the quantity for cap");
	cin>>quantcap;
	cout<<("enter the quantity for lat");
	cin>>quantlat;
	cout<<("enter the quantity for esp");
	cin>>quantesp;
	cout<<"-------Cafe Bill-------"<<endl;
cout<<"Esspresso ("<<*ptresp<<" x "<<*ptrespq<<") = "<<*ptresp * *ptrespq<<endl;
cout<<"Latte ("<<*ptrlat<<" x "<<*ptrlatq<<") = "<<*ptrlat * *ptrlatq<<endl;
cout<<"Cappucino ("<<*ptrcap<<" x "<<*ptrcapq<<") = "<<*ptrcap * *ptrcapq<<endl;
cout<<endl;
int total;
int *ptrtotal=&total;
*ptrtotal=(*ptrcap) * (*ptrcapq)+(*ptrlat)*(*ptrlatq)+(*ptresp)*(*ptrespq);
cout<<"Total Bill = "<<*ptrtotal<<endl;


    return 0;
}#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
    int x;
    cout<<"Enter the no of players ";
    cin>>x;
    
    int *score;
    score=(int*)malloc(x* sizeof(int));
    for (int i=0; i<x; i++)
    {
        cout<<"Enter the score of player "<<i+1<<" : ";
        cin>>score[i];
    }
    for (int i=0; i<x; i++)
    {
        cout<<"Player "<<i+1<<" : "<<score[i]<<endl;
    }
    score=nullptr;

    return 0;
}#include<iostream>
#include<conio.h>
#include<iomanip>
using namespace std;

class Node {

public:

	int data;
	Node* next;
	Node* prev;


	Node(int value)
	{
		this->data = value;
		this->next = nullptr;
		this->prev = nullptr;

	}



};

class DLL
{

public:

	Node* head;
	Node* tail;


	DLL()
	{
		head = nullptr;
		tail = nullptr;
	}

	~DLL()
	{
		Node* curr = head;
		while( curr != nullptr)
			{
				head = head->next;
				delete curr;
				curr = head;
			}
		head = nullptr;
		tail = nullptr;
	}

	//Task 1: Create a destructor



	/*
	* display(): This function is used to display the linked list elements.
	* It will also check if the list is empty
	*/
	void display()
	{
		Node* current = head;

		if (current == nullptr)
		{
			cout << "List is Empty" << endl;
			return;
		}

		while (current != nullptr)
		{
			cout << current->data << endl;
			current = current->next;
		}
	}

	/*Display():
	*	This function is used to display the nodes.
	*	Prev Address: Contains the Address to the Previous Node
	*	Data: Contains the Values
	*	Next Address: Contians the Address of the Next Node
	*	Node Address: Address of the Complete Node
	*/
	void Display() {
		Node* temp = head;
		cout << "\n------------------------------------------------------\n";
		cout << "     Prev Address        |   Data   |     Next Address |   Node Address\n";
		cout << "------------------------------------------------------\n";

		while (temp != nullptr) {
			cout << setw(20) << temp->prev   // shows prev pointer address
				<< " | " << setw(7) << temp->data   // data field
				<< " | " << setw(18) << temp->next  // shows next pointer address
				<< " | " << setw(20) << temp
				<< endl;
			temp = temp->next;
		}
		cout << endl << "Tail: " << tail << endl;
		cout << "------------------------------------------------------\n";
	}



	/*
	* insertAtBegin():
	*	This function is used to insert the Node at the begining.
	*/
	void insertAtBegin(int value)
	{
		Node* newNode = new Node(value);

		newNode->next = head;

		if (head != nullptr)
		{
			head->prev = newNode;
		}
		head = newNode;

		if (head->next == nullptr)
		{
			tail = newNode;
		}
	}

	/* insertAtPos()
	*	This function is used to insert values at specific position
	*	This function will contains your task 2.
	*/
	void insertAtPos(int position, int value)
	{

		if (head == nullptr)
		{
			if (position != 1)
			{
				cout << "Invalid Index..!!" << endl;
				return;
			}
			else
			{
				insertAtBegin(value);
				return;
			}
		}

		Node* current = head;
		Node* newNode = new Node(value);


		//Move Current to One Node Before the desired Location
		for (int i = 1; i < position - 1; i++)
		{
			current = current->next;

		}

		cout << "Traversed: " << current << endl;

		newNode->prev = current;
		newNode->next = current->next;
		if (current->next != nullptr)
		{
			current->next->prev = newNode;
		}
		current->next = newNode;


		/*Task 2
		* Add four items in the linked list
		* And try to add the 5th Item in the linked List.
		* Do you see all the 5 element?
		* If No Fix the code segement.
		*/

	}

	/*
	* deleteFB()
	*	This function is used to delete the node from the front.
	*/

	void deleteFB() {


		if (head == nullptr)
		{
			cout << "List is Empty" << endl;
			return;
		}
		else if (head->next == nullptr)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else
		{
			Node* temp = head;
			head = head->next;
			delete temp;
			head->prev = nullptr;

			/*Task 3:
			* This code delete the elements from the begining of the list
			* Run this function you will see the first the node is deleted.
			* Can you see the problem with the head pointing to the new node?
			* Fix the code segement if you see the problem
			*/

		}
	}
	/*DisplayNode()
	*	The purpose of this function to display the content of the single node.
	*	Run this function you will see the content of more then one node.
	*	Task 4: Fix this.
	*/
	void DisplayNode(Node* node) 
	{
		
    	if (node == nullptr)
    	{
        	cout << "Node not found or empty!" << endl;
        	return;
    	}

    cout << "\n------------------------------------------------------\n";
    cout << "     Prev Address        |   Data   |     Next Address |   Node Address\n";
    cout << "------------------------------------------------------\n";

    cout << setw(20) << node->prev
         << " | " << setw(7) << node->data
         << " | " << setw(18) << node->next
         << " | " << setw(20) << node
         << endl;

    cout << "------------------------------------------------------\n";
	}

	void search(int value)
	{
		Node* current = head;

		while (current != nullptr)
		{
			if (current->data == value)
			{
				cout << "Node found...";
				DisplayNode(current);
			}
			current = current->next;
		}
	}

	void insertAtEnd(int value)
	{
		if (tail == nullptr)
		{
			insertAtBegin(value);
		}
		else
		{
			Node* current = tail;
			Node* newNode = new Node(value);


			current->next = newNode;
			newNode->prev = current;
			newNode->next = nullptr;
			tail = newNode;

		}
	}


};

int main()
{
    DLL list;

    cout << "---------------- INSERTING AT BEGIN ----------------\n";
    list.insertAtBegin(30);
    list.insertAtBegin(20);
    list.insertAtBegin(10);
    list.Display();

    cout << "\n---------------- INSERTING AT END ----------------\n";
    list.insertAtEnd(40);
    list.insertAtEnd(50);
    list.Display();

    cout << "\n---------------- INSERTING AT POSITION ----------------\n";
    list.insertAtPos(3, 25); // insert 25 at position 3
    list.insertAtPos(6, 45); // insert 45 at position 6
    list.Display();

    cout << "\n---------------- DISPLAYING LIST (SIMPLE) ----------------\n";
    list.display(); // prints only data values

    cout << "\n---------------- SEARCH FUNCTION ----------------\n";
    list.search(25); // should find
    list.search(100); // should not find

    cout << "\n---------------- DELETE FROM FRONT ----------------\n";
    list.deleteFB();
    list.Display();

    list.deleteFB();
    list.Display();

    cout << "\n---------------- DISPLAYING SINGLE NODE (DisplayNode) ----------------\n";
    if (list.head != nullptr && list.head->next != nullptr)
    {
        list.DisplayNode(list.head->next); // show a single middle node
    }

    cout << "\n---------------- END OF MAIN ----------------\n";
    return 0;
}#include #include<conio.h> #include using namespace std;

class Node {

public:

int data;
Node* next;
Node* prev;


Node(int value)
{
	this->data = value;
	this->next = nullptr;
	this->prev = nullptr;

}
};

class DLL {

public:

Node* head;
Node* tail;


DLL()
{
	head = nullptr;
	tail = nullptr;
}

~DLL()
{
	Node* curr = head;
	while( curr != nullptr)
		{
			head = head->next;
			delete curr;
			curr = head;
		}
	head = nullptr;
	tail = nullptr;
}

//Task 1: Create a destructor



/*
* display(): This function is used to display the linked list elements.
* It will also check if the list is empty
*/
void display()
{
	Node* current = head;

	if (current == nullptr)
	{
		cout << "List is Empty" << endl;
		return;
	}

	while (current != nullptr)
	{
		cout << current->data << endl;
		current = current->next;
	}
}

/*Display():
*	This function is used to display the nodes.
*	Prev Address: Contains the Address to the Previous Node
*	Data: Contains the Values
*	Next Address: Contians the Address of the Next Node
*	Node Address: Address of the Complete Node
*/
void Display() {
	Node* temp = head;
	cout << "\n------------------------------------------------------\n";
	cout << "     Prev Address        |   Data   |     Next Address |   Node Address\n";
	cout << "------------------------------------------------------\n";

	while (temp != nullptr) {
		cout << setw(20) << temp->prev   // shows prev pointer address
			<< " | " << setw(7) << temp->data   // data field
			<< " | " << setw(18) << temp->next  // shows next pointer address
			<< " | " << setw(20) << temp
			<< endl;
		temp = temp->next;
	}
	cout << endl << "Tail: " << tail << endl;
	cout << "------------------------------------------------------\n";
}



/*
* insertAtBegin():
*	This function is used to insert the Node at the begining.
*/
void insertAtBegin(int value)
{
	Node* newNode = new Node(value);

	newNode->next = head;

	if (head != nullptr)
	{
		head->prev = newNode;
	}
	head = newNode;

	if (head->next == nullptr)
	{
		tail = newNode;
	}
}

/* insertAtPos()
*	This function is used to insert values at specific position
*	This function will contains your task 2.
*/
void insertAtPos(int position, int value)
{

	if (head == nullptr)
	{
		if (position != 1)
		{
			cout << "Invalid Index..!!" << endl;
			return;
		}
		else
		{
			insertAtBegin(value);
			return;
		}
	}

	Node* current = head;
	Node* newNode = new Node(value);


	//Move Current to One Node Before the desired Location
	for (int i = 1; i < position - 1; i++)
	{
		current = current->next;

	}

	cout << "Traversed: " << current << endl;

	newNode->prev = current;
	newNode->next = current->next;
	if (current->next != nullptr)
	{
		current->next->prev = newNode;
	}
	current->next = newNode;


	/*Task 2
	* Add four items in the linked list
	* And try to add the 5th Item in the linked List.
	* Do you see all the 5 element?
	* If No Fix the code segement.
	*/

}

/*
* deleteFB()
*	This function is used to delete the node from the front.
*/

void deleteFB() {


	if (head == nullptr)
	{
		cout << "List is Empty" << endl;
		return;
	}
	else if (head->next == nullptr)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		Node* temp = head;
		head = head->next;
		delete temp;
		head->prev = nullptr;

		/*Task 3:
		* This code delete the elements from the begining of the list
		* Run this function you will see the first the node is deleted.
		* Can you see the problem with the head pointing to the new node?
		* Fix the code segement if you see the problem
		*/

	}
}
/*DisplayNode()
*	The purpose of this function to display the content of the single node.
*	Run this function you will see the content of more then one node.
*	Task 4: Fix this.
*/
void DisplayNode(Node* node) 
{
	
	if (node == nullptr)
	{
    	cout << "Node not found or empty!" << endl;
    	return;
	}

cout << "\n------------------------------------------------------\n";
cout << "     Prev Address        |   Data   |     Next Address |   Node Address\n";
cout << "------------------------------------------------------\n";

cout << setw(20) << node->prev
     << " | " << setw(7) << node->data
     << " | " << setw(18) << node->next
     << " | " << setw(20) << node
     << endl;

cout << "------------------------------------------------------\n";
}

void search(int value)
{
	Node* current = head;

	while (current != nullptr)
	{
		if (current->data == value)
		{
			cout << "Node found...";
			DisplayNode(current);
		}
		current = current->next;
	}
}

void insertAtEnd(int value)
{
	if (tail == nullptr)
	{
		insertAtBegin(value);
	}
	else
	{
		Node* current = tail;
		Node* newNode = new Node(value);


		current->next = newNode;
		newNode->prev = current;
		newNode->next = nullptr;
		tail = newNode;

	}
}
};

int main() { DLL list;

cout << "---------------- INSERTING AT BEGIN ----------------\n";
list.insertAtBegin(30);
list.insertAtBegin(20);
list.insertAtBegin(10);
list.Display();

cout << "\n---------------- INSERTING AT END ----------------\n";
list.insertAtEnd(40);
list.insertAtEnd(50);
list.Display();

cout << "\n---------------- INSERTING AT POSITION ----------------\n";
list.insertAtPos(3, 25); // insert 25 at position 3
list.insertAtPos(6, 45); // insert 45 at position 6
list.Display();

cout << "\n---------------- DISPLAYING LIST (SIMPLE) ----------------\n";
list.display(); // prints only data values

cout << "\n---------------- SEARCH FUNCTION ----------------\n";
list.search(25); // should find
list.search(100); // should not find

cout << "\n---------------- DELETE FROM FRONT ----------------\n";
list.deleteFB();
list.Display();

list.deleteFB();
list.Display();

cout << "\n---------------- DISPLAYING SINGLE NODE (DisplayNode) ----------------\n";
if (list.head != nullptr && list.head->next != nullptr)
{
    list.DisplayNode(list.head->next); // show a single middle node
}

cout << "\n---------------- END OF MAIN ----------------\n";
return 0;
}#include <iostream>
using namespace std;

struct Node {
    int data;       // value of the node
    Node* next;     // pointer to next node
    Node(int d) : data(d), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;   // start of the list
public:
    LinkedList() : head(nullptr) {} 
    void insertAtBeginning(int value) {
    Node* node = new Node(value);
    node->next = head;   // link new node to current head
    head = node;         // move head to new node
}
void insertAtEnd(int value) {
    Node* node = new Node(value);
    if (head == nullptr) {
        head = node;   // if list empty, new node is head
        return;
    }
    Node* cur = head;
    while (cur->next != nullptr) {
        cur = cur->next;
    }
    cur->next = node;  // link last node to new node
}
void insertAtPosition(int value, int pos) {
    if (pos == 0) {
        insertAtBeginning(value);
        return;
    }
    Node* cur = head;
    for (int i = 0; cur != nullptr && i < pos - 1; i++) {
        cur = cur->next;
    }
    if (cur == nullptr) {
        insertAtEnd(value);  // if position too big, insert at end
        return;
    }
    Node* node = new Node(value);
    node->next = cur->next;
    cur->next = node;
}
bool deleteFromBeginning(int* removedValue = nullptr) {
    if (head == nullptr) return false;   // empty list
    Node* temp = head;
    if (removedValue) *removedValue = temp->data;
    head = head->next;                   // move head forward
    delete temp;                         // free memory
    return true;
}
void display() const {
    Node* cur = head;
    while (cur) {
        cout << cur->data;
        if (cur->next) cout << " -> ";
        cur = cur->next;
    }
    cout << "\n";
}
~LinkedList() {
    Node* cur = head;
    while (cur) {
        Node* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
}
};
int main()
{
	
    LinkedList list;

    const int ID_NORMAL_1 = 101;
    const int ID_NORMAL_2 = 102;
    const int ID_NORMAL_3 = 103;
    const int ID_EMERGENCY = 999;
    const int ID_SPECIAL_BOOKING = 555;

    cout << "--- Operations on Linked List ---\n\n";

   
    list.insertAtEnd(ID_NORMAL_1);
    list.insertAtEnd(ID_NORMAL_2);
    list.insertAtEnd(ID_NORMAL_3);
    cout << "Initial List after adding Node:\n";
    list.display();
    cout << "\n";

    
    list.insertAtBeginning(ID_EMERGENCY);
    cout << "After adding an Node at beginning:\n";
    list.display();
    cout << "\n";

    
    try {
        list.insertAtPosition(ID_SPECIAL_BOOKING, 2);
        cout << "After inserting Node at some position 2:\n";
        list.display();
    }  
	    catch (const out_of_range& e) {
        cerr << "Error inserting at position: " << e.what() << "\n";
    }
    cout << "\n";

    
    int removed;
    if (list.deleteFromBeginning(&removed)) {
        cout << "After deleting first Node :\n";
        list.display();
    }  
	    else {
        cout << "Queue was empty, no Node added.\n";
    }
    cout << "\n--- Simulation End ---\n";

    return 0;

} #include <iostream>
using namespace std;

struct patient{
	int ID;
	patient* next;
	patient* prev;
	patient(int id)
	{
		ID=id;
		next=nullptr;
		prev=nullptr;
	}
};
class ER
{
	public:
		patient* head;
		patient* tail;
		
		
		ER()
		{
			head=nullptr;
			tail=nullptr;
		
		}
		void insertatbeginning(int id)
		{
			patient* node=new patient(id);
			if (head == nullptr)
			{
				head=node;
				tail=node;
			}
			if (head != nullptr)
			{
				node->next=head;
				head->prev=node;
				head=node;
			}
			cout<<"Patient is admitted"<<endl;
		}
		void insertatend(int id)
		{
			patient* node=new patient(id);
			if (head == nullptr)
			{
				head=node;
				tail=node;
			}
			if (head != nullptr)
			{
				node->prev=tail;
				tail->next=node;
				tail=node;
			}
			cout<<"Patient is admitted!"<<endl;
		}
		void insertatpos(int id,int pos)
		{
			if (pos < 1)
			{
				cout<<"Patient can't be added at this Position";
				return;
			}
			if (pos == 1)
			{
				insertatbeginning(id);
			    return;
		    }
		    patient* node=new patient(id);
		    patient* curr=head;
		    for (int i;i<pos-1;i++)
		    {
		    	curr=curr->next;
			}
			node->prev = curr;
		    node->next = curr->next;
		    if (curr->next != nullptr)
		    {
			    curr->next->prev =node;
		    }
		    curr->next = node;
		    cout<<"Patient is admitted"<<endl;
		}
		void deletefrombeginning()
		{
			 if (head == nullptr)
			 {
			 	cout<<"No Patients to treat";
			 	return;
			 }
			 if (head->next == nullptr)
			 {
			 	delete head;
			 	delete tail;
			 	cout<<"Patient is treated";
			 	return;
			 }
			 patient* temp=head;
			 if (head->next != nullptr)
			 {
			 	head=head->next;
			 	head->prev=nullptr;
			 	delete temp;
			 	cout<<"Patient is treated";
			 }
			 
		}
};
int main()
{
	int id,pos;
	ER queue;
	int choice;

    do {
        cout << "\n===== Hospital Emergency Queue System =====\n";
        cout << "1. Add walk in patient\n";
        cout << "2. Treat the patient\n";
        cout << "3. Add critical patient\n";
        cout << "4. Add patient in between queue\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout<<"Enter patient ID"<<endl;
                cin>>id;
            	queue.insertatend(id);
            	break;
            	
            case 2:
            	queue.deletefrombeginning();
				break;
			
			case 3:
            	cout<<"Enter patient ID"<<endl;
            	cin>>id;
            	queue.insertatbeginning(id);
				break;
				
			case 4:
            	cout<<"Enter patient ID"<<endl;
            	cin>>id;
            	cout<<"Enter position"<<endl;
            	cin>>pos;
            	queue.insertatpos(id,pos);
				break;
			
            case 5:
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid choice, please try again." << endl;
        }

    } while (choice != 6);

    return 0;
}#include <iostream>
using namespace std;

int generateCode(int x)
{
    int y=1;
    if (x==0)
    {
        cout<<"your secret code is 1"<<endl;
    }
    else{
        for (int i=1; i<=x;i++)
        {
            y*=i;
        }
    }
      return y;
}

int main()
{
    int x;
    cout<<"enter the number to get a secret code ";
    cin>>x;
    int (*codeptr)(int x);
    codeptr=generateCode;
    cout<<"your secret code is "<<codeptr(x)<<endl;


    return 0;
}#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

void bubbleSort(int arr[], int n) {
    bool swapped;
    for(int i = 0; i < n - 1; i++) {
        swapped = false;
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if(!swapped)
            break;
    }
}

int main() {
    ifstream fin("numbers.txt");
    if (!fin) {
        cout << "Error in opening file\n";
        return 0;
    }

    string line, token;
    getline(fin, line);
    fin.close();

    int count = 1;
    for (char c : line) {
        if (c == ',')
            count++;
    }

    int* arr = new int[count];
    int n = 0;
    stringstream ss(line);
    while (getline(ss, token, ',')) {
        arr[n++] = stoi(token);
    }

    auto start = high_resolution_clock::now();
    bubbleSort(arr, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Sorted Array: ";
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << "\nTime taken by bubble sort: "
         << duration.count() << " milliseconds\n";

    delete[] arr;
    return 0;
}#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

struct Stu {
    int id;
    char name[100];
    char dept[10];
    int sem;
    float gpa;
    int cred;
    int yr;
    Stu* nxt;
};

Stu* first = nullptr;
int total = 0;

// --- LINKED LIST UTILITIES ---

void load() {
    ifstream in("students_data.txt");
    if (!in) {
        cout << "Error: students_data.txt not found!\n";
        return;
    }
    in >> total;
    Stu* lastone = nullptr;
    for (int i = 0; i < total; i++) {
        Stu* n = new Stu;
        in >> n->id;
        in.ignore(); // skip space
        
        // Read name carefully
        char firstN[50], lastN[50];
        in >> firstN >> lastN;
        strcpy(n->name, firstN);
        strcat(n->name, " ");
        strcat(n->name, lastN);
        
        in >> n->dept >> n->sem >> n->gpa >> n->cred >> n->yr;
        n->nxt = nullptr;
        if (!first) first = n;
        else lastone->nxt = n;
        lastone = n;
    }
    in.close();
}

Stu* duplicateList(Stu* head) {
    if (!head) return nullptr;
    Stu* newHead = nullptr;
    Stu* newLast = nullptr;
    while (head) {
        Stu* n = new Stu;
        *n = *head;
        n->nxt = nullptr;
        if (!newHead) newHead = n;
        else newLast->nxt = n;
        newLast = n;
        head = head->nxt;
    }
    return newHead;
}

void freeList(Stu* head) {
    while (head) {
        Stu* t = head;
        head = head->nxt;
        delete t;
    }
}

// --- MERGE SORT IMPLEMENTATION (O(n log n)) ---
// Selection sort is too slow for 1,000,000 records.



Stu* split(Stu* head) {
    Stu* fast = head;
    Stu* slow = head;
    while (fast->nxt && fast->nxt->nxt) {
        fast = fast->nxt->nxt;
        slow = slow->nxt;
    }
    Stu* temp = slow->nxt;
    slow->nxt = nullptr;
    return temp;
}

// 1. Merge for CGPA (File 1)
Stu* mergeCGPA(Stu* a, Stu* b) {
    if (!a) return b;
    if (!b) return a;
    bool aBetter = (a->gpa > b->gpa) || (a->gpa == b->gpa && a->cred > b->cred);
    if (aBetter) {
        a->nxt = mergeCGPA(a->nxt, b);
        return a;
    } else {
        b->nxt = mergeCGPA(a, b->nxt);
        return b;
    }
}

// 2. Merge for Year (File 2)
Stu* mergeYear(Stu* a, Stu* b) {
    if (!a) return b;
    if (!b) return a;
    bool aBetter = (a->yr < b->yr) || (a->yr == b->yr && a->id < b->id);
    if (aBetter) {
        a->nxt = mergeYear(a->nxt, b);
        return a;
    } else {
        b->nxt = mergeYear(a, b->nxt);
        return b;
    }
}

// 3. Merge for Dept (File 3)
Stu* mergeDept(Stu* a, Stu* b) {
    if (!a) return b;
    if (!b) return a;
    int d = strcmp(a->dept, b->dept);
    bool aBetter = (d < 0) || (d == 0 && a->sem < b->sem) || (d == 0 && a->sem == b->sem && a->gpa > b->gpa);
    if (aBetter) {
        a->nxt = mergeDept(a->nxt, b);
        return a;
    } else {
        b->nxt = mergeDept(a, b->nxt);
        return b;
    }
}

// 4. Merge for Name (File 4)
Stu* mergeName(Stu* a, Stu* b) {
    if (!a) return b;
    if (!b) return a;
    if (strcmp(a->name, b->name) <= 0) {
        a->nxt = mergeName(a->nxt, b);
        return a;
    } else {
        b->nxt = mergeName(a, b->nxt);
        return b;
    }
}

// Generic MergeSort caller
typedef Stu* (*MergeFunc)(Stu*, Stu*);
Stu* mergeSort(Stu* head, MergeFunc m) {
    if (!head || !head->nxt) return head;
    Stu* second = split(head);
    return m(mergeSort(head, m), mergeSort(second, m));
}

// --- FILE GENERATION ---

void makeFile1() {
    Stu* copy = mergeSort(duplicateList(first), mergeCGPA);
    ofstream out("ranked_by_cgpa.txt");
    out << left << setw(6) << "Rank" << " | " << setw(8) << "ID" << " | " << setw(20) << "Name" << " | " << setw(5) << "Dept" << " | " << "GPA\n";
    int r = 1;
    for (Stu* c = copy; c; c = c->nxt) {
        out << left << setw(6) << r++ << " | " << setw(8) << c->id << " | " << setw(20) << c->name << " | " << setw(5) << c->dept << " | " << fixed << setprecision(2) << c->gpa << "\n";
    }
    freeList(copy);
}

void makeFile2() {
    Stu* copy = mergeSort(duplicateList(first), mergeYear);
    ofstream out("sorted_by_enrollment.txt");
    int curYr = -1; float sum = 0; int cnt = 0;
    for (Stu* c = copy; c; c = c->nxt) {
        if (c->yr != curYr) {
            if (curYr != -1) out << "Avg CGPA for " << curYr << ": " << (sum / cnt) << "\n\n";
            curYr = c->yr; sum = 0; cnt = 0;
            out << "=== Year " << curYr << " ===\n";
        }
        out << c->id << " " << c->name << " " << c->gpa << "\n";
        sum += c->gpa; cnt++;
    }
    if (cnt > 0) out << "Avg CGPA for " << curYr << ": " << (sum / cnt) << "\n";
    freeList(copy);
}

void makeFile3() {
    Stu* copy = mergeSort(duplicateList(first), mergeDept);
    ofstream out("department_analysis.txt");
    char curDep[10] = ""; int depCnt = 0; float sumG = 0;
    for (Stu* c = copy; c; c = c->nxt) {
        if (strcmp(c->dept, curDep) != 0) {
            if (depCnt > 0) out << "Dept Avg: " << (sumG / depCnt) << "\n\n";
            strcpy(curDep, c->dept); sumG = 0; depCnt = 0;
            out << "=== Dept: " << curDep << " ===\n";
        }
        out << c->name << " GPA: " << c->gpa << "\n";
        sumG += c->gpa; depCnt++;
    }
    freeList(copy);
}

void makeFile4() {
    Stu* tiers[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
    const char* titles[] = {"Elite", "High Achiever", "Good Standing", "Satisfactory", "Needs Improvement"};
    
    for (Stu* c = first; c; c = c->nxt) {
        Stu* n = new Stu; *n = *c; n->nxt = nullptr;
        int idx = (c->gpa >= 3.7) ? 0 : (c->gpa >= 3.3) ? 1 : (c->gpa >= 3.0) ? 2 : (c->gpa >= 2.5) ? 3 : 4;
        n->nxt = tiers[idx]; tiers[idx] = n;
    }

    ofstream out("performance_tiers.txt");
    for (int i = 0; i < 5; i++) {
        tiers[i] = mergeSort(tiers[i], mergeName);
        out << "--- " << titles[i] << " ---\n";
        for (Stu* c = tiers[i]; c; c = c->nxt) out << c->name << " (" << c->gpa << ")\n";
        out << endl;
        freeList(tiers[i]);
    }
}

int main() {
    cout << "Loading records..." << endl;
    load();
    if (!first) return 1;
    
    cout << "Sorting and generating files (this will be fast)..." << endl;
    makeFile1();
    makeFile2();
    makeFile3();
    makeFile4();
    
    freeList(first);
    cout << "Success! All files generated.\n";
    return 0;
}#include <iostream>
using namespace std;

int generateCode(int x)
{
    int y=1;
    if (x!=0){
        for (int i=1; i<=x;i++)
        {
            y*=i;
        }
    }
      return y;
}

int main()
{
    int x;
    cout<<"enter the number to get a secret code ";
    cin>>x;
    int (*codeptr)(int x);
    codeptr=generateCode;
    cout<<"your secret code is "<<codeptr(x)<<endl;


    return 0;
}