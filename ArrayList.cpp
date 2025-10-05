#include <iostream>
using namespace std;
create
copy
clear
insert
remove
get
update
display
find
length
class ArrayList {
    private:
        static const string storedType = "heap allocated array of integers";
        int* arr;
        int* curr;
        int capacity;// maximum number of elements
        int length;//current number of elements
    public:
        static void displayFunction{
            cout << "variable static string = ArrayList::storedType" << endl;
            
        
        }
        ArrayList(int Size=0) : capacity(Size),length(0) ,cur(nullptr) {
            arr = new int[capacity];
        }
        ~ArrayList() {
            delete[] arr;

        }
        void create(int Size) {
            capacity = Size;
            arr = new int[capacity];
            length = 0;
            curr = nullptr;
        }
        void start() {
            curr = arr;
        }
        void end() {
            curr = arr + length - 1;
        }
        void next(){
            curr++;
        }
        void prev(){
            curr--;
        }
        
        int getCapacity() const {
            return capacity;
        }
        int getSize() const {
            return size;
        }
        bool isEmpty() const {
            return size == 0;
        }
        bool isFull() const {
            return size == capacity;
        }
        void display() const {
            for (int i = 0; i < size; i++) {
                cout << *(curr+i) << " ";
            }
            cout << endl;
        }
        void clear() {
            size = 0;
            curr = nullptr;
        }
        void add(int value) {
            if (isFull()) {// if list is full
                cout << "List is full. Cannot add more elements." << endl;
                return;
            }
            curr = arr;// point to the start of the array
            for(int i=0;i<size;i++){// traverse to the end of the array
                curr++;// move the pointer to the next element
            }
            curr = value;// add the value at the end
            size++;// increase the size
        }
        int get(int index) const {
            if(capacity==0){// if list is empty
                cout<<"List is empty."<<endl;
                return -1;
            }
            if (index < 0 || index >= size) {// if index is out of bounds
                cout << "Index out of bounds." << endl;
                return -1;
            }
            curr = arr;// point to the start of the array
            for(int i=0;i<index;i++){// traverse to the index
                curr++;// move the pointer to the next element
            }
            return *curr;// return the value at the index
        }
        void remove(int index) {
            if(capacity==0){// if list is empty
                cout<<"List is empty."<<endl;
                return;
            }
            if (index < 0 || index >= size) {// if index is out of bounds
                cout << "Index out of bounds." << endl;
                return;
            }
            curr = arr;// point to the start of the array
            for(int i=0;i<index;i++){// traverse to the index
                curr++;// move the pointer to the next element
            }
            for (int i = index; i < size - 1; i++) {// shift elements to the left
                *(curr+i) = *(curr+i+1);
            }
            size--;// decrease the size
        }
        void insert(int index, int value) {
            if(capacity==0){// if list is empty
                cout<<"List is empty."<<endl;
                return;
            }
            if (index < 0 || index >= size) {// if index is out of bounds
                cout << "Index out of bounds." << endl;
                return;
            }
            curr = arr;// point to the start of the array
            for(int i=0;i<index;i++){// traverse to the index
                curr++;// move the pointer to the next element
            }
            *curr = value;// set the value at the index
        }

};
int main(){
    ArrayList list(3);
    cout << "Capacity: " << list.getCapacity() << endl;
    list.add(5);
    cout << "Size: " << list.getSize() << endl;
    cout << "Is Empty: " << (list.isEmpty() ? "Yes":"No") << endl;
    list.add(10);
    list.add(15);
    cout << "Is Full: " << (list.isFull() ? "Yes":"No") << endl;
    list.remove(1);
    list.display();
    list.insert(1,20);
    list.display();
    list.clear();
    cout << "Size after clear: " << list.getSize() << endl;
    list.get(0);
    return 0;
}