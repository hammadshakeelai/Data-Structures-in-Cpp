#include<iostream>
#include<fstream>
#include<string>
#include <chrono>  // For timing measurement
using namespace std::chrono;
using namespace std;
class ArrayList {
public:
    int* arr;
    int* curr;
    int capacity;// max number# of elements
    int length;// current number of elements in arr
    int resizeFactor;

public:
    ArrayList(int cap = 10) {
        create(cap);
        curr = arr;
        resizeFactor = 2;
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
    bool isFull() {
        return length == capacity;
    }
    bool isEmpty() {
        if (length == 0) {
            return true;
        }
        return false;
    }
    void resize() {
        int newCapacity = capacity * resizeFactor;
        int* newArr = new int[newCapacity];
        for (int i = 0; i < length; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        capacity = newCapacity;
        curr = arr;
        cout << "Array resized to capacity: " << capacity << endl;
    }
    void insert(int value) {
        if (isFull()) {
            resize();
        }
        curr = arr + length;
        *curr = value;
        length++;
    }
    void print() {
        if (isEmpty()) {
            cout << "Array is empty!" << endl;
            return;
        }

        cout << "Array elements (" << length << "/" << capacity << "): ";
        for (int i = 0; i < length; i++) {
            cout << arr[i];
            if (i < length - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
    void start() {
        curr = arr;
    }
    void end() {
        curr = arr + (length - 1);
    }
    void next() {
        if (curr < arr + (length - 1)) {
            curr++;
        }
    }
    void back() {
        if (curr > arr) {
            curr--;
        }
    }
    void bubbleSort() {
        bool swapped;
        int n = length;
        for (int i = 0; i < n - 1; i++) {
            swapped = false;
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped)
                break;
        }
    }
};

int main() {
	ifstream MyFile("filename.txt");
	string line;
    getline(MyFile,line);
	cout << line << endl;
    int num = 0;
    //cout << "\n\n\n;";
    //cout << "int num = 0;\n";
    ArrayList list;
    for (char ch : line) {
        if (ch == ',') {
            list.insert(num);
            //cout << "inserted into array;\nnum = 0;\n";
            num = 0;
        }
        else if (ch == 'X') {
            cout << "continue;\n";
            continue;
        }
        else {
            //cout << "num *= 10;\nn += (ch % 48);\n";
            num *= 10;
            num += (ch % 48);
        }
    }
    //list.print();
    cout << "starting bubbleSort \n";
    //list.bubbleSort();
    //for(int i=0;i<19;i++)
    //list.print();

	MyFile.close();


    // Measure time
    auto start = high_resolution_clock::now();
    list.bubbleSort();
    auto stop = high_resolution_clock::now();
    list.print();
    // Calculate duration
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken: " << duration.count() << " microseconds\n";
    cout << "           = " << duration.count() / 1000.0 << " milliseconds\n";

}