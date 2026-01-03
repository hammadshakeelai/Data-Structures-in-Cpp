#include<iostream>
#include<string>
#include<fstream>
//off_t lseek(int fd, off_t offset, int whence);
using namespace std;
struct Node {
    int studentID;
    string studentName;
    string DepartmentCode;
    int Semester;
    double CGPA;
    int CeditHoursCompleted;
    int EnrollmentYear;
    Node* next;
    Node(int s_id, string s_n, string s_d_code, int s_sems, double s_cgpa, int s_CRH, int s_en_year) {
        this->studentID = s_id;
        this->studentName = s_n;
        this->DepartmentCode = s_d_code;
        this->Semester = Semester;
        this->CGPA = s_cgpa;
        this->CeditHoursCompleted = s_CRH;
        this->EnrollmentYear = s_en_year;
        next = nullptr;
    }
};
class LinkedList {
public:
    int Total_Number_of_Students;
    Node* head;
public:
    LinkedList(int t_s) {
        this->Total_Number_of_Students = t_s;
        head = nullptr;
    }
    ~LinkedList() {
        while (head != nullptr) {
            deleteFromBeginning();
        }

        //        Node* cur = head;
        //        Node *temp =nullptr;
        //        while(cur->next != nullptr){
        //            temp = cur->next;
        //            delete cur;
        //            cur = temp;
        //        }

    }
    void insertAtBeginning(int s_id, string s_n, string s_d_code, int s_sems, double s_cgpa, int s_CRH, int s_en_year) {
        Node* temp = new Node(s_id, s_n, s_d_code, s_sems, s_cgpa, s_CRH, s_en_year);
        temp->next = head;
        head = temp;
    }
    void insertAtEnd(int s_id, string s_n, string s_d_code, int s_sems, double s_cgpa, int s_CRH, int s_en_year) {
        Node* temp = new Node(s_id, s_n, s_d_code, s_sems, s_cgpa, s_CRH, s_en_year);
        if (head == nullptr) {
            head = temp;
            return;
        }
        Node* cur = head;
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = temp;
    }
    void insertAtPosition(int s_id, string s_n, string s_d_code, int s_sems, double s_cgpa, int s_CRH, int s_en_year, int position) {
        if (position == 0) {
            insertAtBeginning(s_id, s_n, s_d_code, s_sems, s_cgpa, s_CRH, s_en_year);
            return;
        }
        Node* temp = new Node(s_id, s_n, s_d_code, s_sems, s_cgpa, s_CRH, s_en_year);
        Node* cur = head;
        for (int i = 0; i < position - 1 && cur != nullptr; i++) {
            cur = cur->next;
        }
        if (cur == nullptr) {
            cout << "Position out of bounds. Inserting at the end." << endl;
            insertAtEnd(s_id, s_n, s_d_code, s_sems, s_cgpa, s_CRH, s_en_year);
            return;
        }
        temp->next = cur->next;
        cur->next = temp;
    }
    bool deleteFromBeginning(int* removed = nullptr) {
        if (head == nullptr) {
            cout << "List is empty. Cannot delete." << endl;
            return false;
        }
        Node* temp = head;
        if (removed != nullptr) {
            *removed = head->studentID;
        }
        head = head->next;
        delete temp;
        return true;
    }
    void deleteFromEnd() {
        if (head == nullptr) {
            cout << "List is empty. Cannot delete." << endl;
            return;
        }
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return;
        }
        Node* cur = head;
        while (cur->next->next != nullptr) {
            cur = cur->next;
        }
        delete cur->next;
        cur->next = nullptr;
    }
    void display() {
        Node* cur = head;
        while (cur != nullptr) {
            cout << "<" << cur->studentID << "> <" << cur->studentName << "> <" << cur->DepartmentCode << "> <" << cur->Semester << "> <" << cur->CGPA << "> <" << cur->CeditHoursCompleted << "> <" << cur->EnrollmentYear << "> " << " ->\n";
            cur = cur->next;
        }
        cout << "nullptr" << endl;
    }

};
void selectionsort(LinkedList* arr) {
    Node* temp = arr->head, *cur = temp;
    for (int i = 0; i < 999999; i++) {
        cur = temp; 
        for (int j = i + 1; j < 1000000; j++) {
            if ( <= arr[j]) {
                continue;
            }
            else {
                temp =;
                cur = ;
            }
        }
        arr[cur] = arr[i];
        arr[i] = temp;
        cur = cur->next;
    }
}
void swapData(Node* a, Node* b) {
    Node tmp = *a;
    *a = *b;
    *b = tmp;
    Node* an = a->next;
    Node* bn = b->next;
    a->next = an;
    b->next = bn;
}
int main() {
     
    ifstream scan("students_data.txt");
    if (!scan.is_open()) {
        cerr << "Error: Unable to open file!" << endl;
        return 1;
    }
    int num;
    scan >> num;
    const int line = num;
    scan.ignore();
    LinkedList data(line);

    

    int sid, sem, ch, ey; double cgpa; string sname, dcode;

    for (int i = 0; i < 2; i++) {
        scan >> sid >> sname;

        
        scan >> dcode >> sem >> cgpa >> ch >> ey;
        scan.ignore();
        cout << sid << " " << sname << " " << dcode << " " << sem << " " << cgpa << " " << ch << " " << ey << endl;
        data.insertAtEnd(sid, sname, dcode, sem, cgpa, ch, ey);
    }
    data.display();
    scan.close();
}