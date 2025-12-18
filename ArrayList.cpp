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
        void create(int cap) {
            capacity = cap;
            length = 0;
            arr = new int[capacity];
            curr = arr;
        }
};
int main(){
    ArrayList list(1000);
    return 0;
}