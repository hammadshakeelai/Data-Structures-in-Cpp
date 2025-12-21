#include<iostream>
#include<string>
#include<fstream>
using namespace std;

struct Node {
    int studentID;
    string studentName;
    string DepartmentCode;
    int Semester;
    double CGPA;
    int CreditHoursCompleted;
    int EnrollmentYear;
    Node* next;
    
    Node(int s_id, string s_n, string s_d_code, int s_sems, double s_cgpa, int s_CRH, int s_en_year) {
        this->studentID = s_id;
        this->studentName = s_n;
        this->DepartmentCode = s_d_code;
        this->Semester = s_sems;
        this->CGPA = s_cgpa;
        this->CreditHoursCompleted = s_CRH;
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
    }
    
    void insertAtBeginning(int s_id, string s_n, string s_d_code, int s_sems, 
                          double s_cgpa, int s_CRH, int s_en_year) {
        Node* temp = new Node(s_id, s_n, s_d_code, s_sems, s_cgpa, s_CRH, s_en_year);
        temp->next = head;
        head = temp;
    }
    
    void insertAtEnd(int s_id, string s_n, string s_d_code, int s_sems, 
                     double s_cgpa, int s_CRH, int s_en_year) {
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
            cout << "<" << cur->studentID << "> <" << cur->studentName << "> <" 
                 << cur->DepartmentCode << "> <" << cur->Semester << "> <" 
                 << cur->CGPA << "> <" << cur->CreditHoursCompleted << "> <" 
                 << cur->EnrollmentYear << "> ->\n";
            cur = cur->next;
        }
        cout << "nullptr" << endl;
    }
    
    // Helper function to count nodes
    int countNodes() {
        int count = 0;
        Node* cur = head;
        while (cur != nullptr) {
            count++;
            cur = cur->next;
        }
        return count;
    }
};

// Selection sort for linked list by CGPA (descending)
void sortByCGPA(LinkedList& list) {
    Node* current = list.head;
    
    while (current != nullptr) {
        Node* maxNode = current;
        Node* temp = current->next;
        
        while (temp != nullptr) {
            if (temp->CGPA > maxNode->CGPA) {
                maxNode = temp;
            }
            temp = temp->next;
        }
        
        // Swap data
        if (maxNode != current) {
            int tempID = current->studentID;
            string tempName = current->studentName;
            string tempDept = current->DepartmentCode;
            int tempSem = current->Semester;
            double tempCGPA = current->CGPA;
            int tempCH = current->CreditHoursCompleted;
            int tempYear = current->EnrollmentYear;
            
            current->studentID = maxNode->studentID;
            current->studentName = maxNode->studentName;
            current->DepartmentCode = maxNode->DepartmentCode;
            current->Semester = maxNode->Semester;
            current->CGPA = maxNode->CGPA;
            current->CreditHoursCompleted = maxNode->CreditHoursCompleted;
            current->EnrollmentYear = maxNode->EnrollmentYear;
            
            maxNode->studentID = tempID;
            maxNode->studentName = tempName;
            maxNode->DepartmentCode = tempDept;
            maxNode->Semester = tempSem;
            maxNode->CGPA = tempCGPA;
            maxNode->CreditHoursCompleted = tempCH;
            maxNode->EnrollmentYear = tempYear;
        }
        
        current = current->next;
    }
}

// Selection sort for linked list by Enrollment Year
void sortByEnrollment(LinkedList& list) {
    Node* current = list.head;
    
    while (current != nullptr) {
        Node* minNode = current;
        Node* temp = current->next;
        
        while (temp != nullptr) {
            if (temp->EnrollmentYear < minNode->EnrollmentYear ||
                (temp->EnrollmentYear == minNode->EnrollmentYear && 
                 temp->studentID < minNode->studentID)) {
                minNode = temp;
            }
            temp = temp->next;
        }
        
        // Swap data
        if (minNode != current) {
            int tempID = current->studentID;
            string tempName = current->studentName;
            string tempDept = current->DepartmentCode;
            int tempSem = current->Semester;
            double tempCGPA = current->CGPA;
            int tempCH = current->CreditHoursCompleted;
            int tempYear = current->EnrollmentYear;
            
            current->studentID = minNode->studentID;
            current->studentName = minNode->studentName;
            current->DepartmentCode = minNode->DepartmentCode;
            current->Semester = minNode->Semester;
            current->CGPA = minNode->CGPA;
            current->CreditHoursCompleted = minNode->CreditHoursCompleted;
            current->EnrollmentYear = minNode->EnrollmentYear;
            
            minNode->studentID = tempID;
            minNode->studentName = tempName;
            minNode->DepartmentCode = tempDept;
            minNode->Semester = tempSem;
            minNode->CGPA = tempCGPA;
            minNode->CreditHoursCompleted = tempCH;
            minNode->EnrollmentYear = tempYear;
        }
        
        current = current->next;
    }
}

// Function to write list to file
void writeToFile(LinkedList& list, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error: Cannot open " << filename << endl;
        return;
    }
    
    Node* cur = list.head;
    while (cur != nullptr) {
        outFile << cur->studentID << " " << cur->studentName << " " 
                << cur->DepartmentCode << " " << cur->Semester << " " 
                << cur->CGPA << " " << cur->CreditHoursCompleted << " " 
                << cur->EnrollmentYear << endl;
        cur = cur->next;
    }
    outFile.close();
}

// Function to create a copy of linked list
LinkedList copyList(LinkedList& original) {
    LinkedList copy(original.Total_Number_of_Students);
    Node* cur = original.head;
    
    while (cur != nullptr) {
        copy.insertAtEnd(cur->studentID, cur->studentName, cur->DepartmentCode,
                         cur->Semester, cur->CGPA, cur->CreditHoursCompleted,
                         cur->EnrollmentYear);
        cur = cur->next;
    }
    return copy;
}

// Fixed your original selection sort function
void selectionsort(LinkedList* arr) {
    Node* current = arr->head;
    int nodeCount = arr->countNodes();
    
    for (int i = 0; i < nodeCount - 1 && current != nullptr; i++) {
        Node* minNode = current;
        Node* compare = current->next;
        
        while (compare != nullptr) {
            if (compare->studentID < minNode->studentID) {
                minNode = compare;
            }
            compare = compare->next;
        }
        
        // Swap data
        if (minNode != current) {
            // Swap all data fields
            int tempID = current->studentID;
            string tempName = current->studentName;
            string tempDept = current->DepartmentCode;
            int tempSem = current->Semester;
            double tempCGPA = current->CGPA;
            int tempCH = current->CreditHoursCompleted;
            int tempYear = current->EnrollmentYear;
            
            current->studentID = minNode->studentID;
            current->studentName = minNode->studentName;
            current->DepartmentCode = minNode->DepartmentCode;
            current->Semester = minNode->Semester;
            current->CGPA = minNode->CGPA;
            current->CreditHoursCompleted = minNode->CreditHoursCompleted;
            current->EnrollmentYear = minNode->EnrollmentYear;
            
            minNode->studentID = tempID;
            minNode->studentName = tempName;
            minNode->DepartmentCode = tempDept;
            minNode->Semester = tempSem;
            minNode->CGPA = tempCGPA;
            minNode->CreditHoursCompleted = tempCH;
            minNode->EnrollmentYear = tempYear;
        }
        
        current = current->next;
    }
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
    
    int sid, sem, ch, ey; 
    double cgpa; 
    string sname, dcode;
    
    for (int i = 0; i < line; i++) {
        scan >> sid >> sname >> dcode >> sem >> cgpa >> ch >> ey;
        scan.ignore();
        
        cout << "Read: " << sid << " " << sname << " " << dcode << " " 
             << sem << " " << cgpa << " " << ch << " " << ey << endl;
             
        data.insertAtEnd(sid, sname, dcode, sem, cgpa, ch, ey);
    }
    
    cout << "\nOriginal Data:\n";
    data.display();
    
    // Create copies for sorting
    LinkedList cgpaSorted = copyList(data);
    LinkedList enrollmentSorted = copyList(data);
    
    // Sort by CGPA
    sortByCGPA(cgpaSorted);
    writeToFile(cgpaSorted, "ranked_by_cgpa.txt");
    
    // Sort by Enrollment
    sortByEnrollment(enrollmentSorted);
    writeToFile(enrollmentSorted, "sorted_by_enrollment.txt");
    
    // Test your selection sort
    cout << "\nAfter sorting by student ID:\n";
    selectionsort(&data);
    data.display();
    
    scan.close();
    return 0;
}