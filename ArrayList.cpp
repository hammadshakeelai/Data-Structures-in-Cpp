#include <iostream>
using namespace std;

class ArrayList {
    private:
        int* arr;
        int* curr;
        int capacity;// maximum number of elements
        int length;//current number of elements
    public:
        ArrayList(int cap) {
            create(cap);
            curr = arr;
        }
        ~ArrayList() {
            delete[] arr;
        }
        void start() {
            curr = arr;
        }
        void next() {
            if (curr < arr + length - 1) {
                curr++;
            } else {
                cout << "Already at the end of the list." << endl;
            }
        }
        void end() {
            curr = arr + length - 1;
        }
        void create(int cap) {
            capacity = cap;
            length = 0;
            arr = new int[capacity];
            curr = arr;
        }
        copy
        void clear(){
            length = 0;
        }
        insert
        remove
        int get(int index) {
            if (index < 0 || index >= length) {
                cout << "Index out of bounds." << endl;
                return -1; // or throw an exception
            }
            return *curr;
        }
        update
        display
        find
        length     
        
        

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