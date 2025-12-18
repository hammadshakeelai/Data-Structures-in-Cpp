#include <iostream>
using namespace std;

class ArrayList {
private:
    int* arr;
    int* curr;
    int capacity;  // maximum number of elements
    int length;    // current number of elements
    int resizeFactor;  // factor by which to increase capacity when needed

public:
    // Constructor with initial capacity
    ArrayList(int cap = 10) {
        create(cap);
        curr = arr;
        resizeFactor = 2;  // double capacity when resizing
    }

    // Destructor
    ~ArrayList() {
        delete[] arr;
    }

    // Create/Initialize the array list
    void create(int cap) {
        capacity = cap;
        length = 0;
        arr = new int[capacity];
        curr = arr;
    }

    // Check if the array is full
    bool isFull() {
        return length == capacity;
    }

    // Check if the array is empty
    bool isEmpty() {
        return length == 0;
    }

    // Resize the array when capacity is reached
    void resize() {
        int newCapacity = capacity * resizeFactor;
        int* newArr = new int[newCapacity];

        // Copy elements to new array
        for (int i = 0; i < length; i++) {
            newArr[i] = arr[i];
        }

        // Delete old array and update pointer
        delete[] arr;
        arr = newArr;
        capacity = newCapacity;
        
        // Reset curr pointer to start
        curr = arr;
        
        cout << "Array resized to capacity: " << capacity << endl;
    }

    // Insert element at the end
    void insert(int value) {
        if (isFull()) {
            resize();
        }
        
        // Move to the correct position
        curr = arr + length;
        *curr = value;
        length++;
    }

    // Insert element at specific index
    void insertAt(int index, int value) {
        if (index < 0 || index > length) {
            cout << "Error: Index out of bounds!" << endl;
            return;
        }

        if (isFull()) {
            resize();
        }

        // Shift elements to the right
        for (int i = length; i > index; i--) {
            arr[i] = arr[i - 1];
        }

        // Insert new element
        arr[index] = value;
        length++;
    }

    // Insert element at the beginning
    void insertAtStart(int value) {
        insertAt(0, value);
    }

    // Remove element at specific index
    void removeAt(int index) {
        if (index < 0 || index >= length) {
            cout << "Error: Index out of bounds!" << endl;
            return;
        }

        // Shift elements to the left
        for (int i = index; i < length - 1; i++) {
            arr[i] = arr[i + 1];
        }

        length--;
    }

    // Remove last element
    void remove() {
        if (isEmpty()) {
            cout << "Error: Array is empty!" << endl;
            return;
        }
        length--;
    }

    // Remove first element
    void removeFromStart() {
        removeAt(0);
    }

    // Get element at specific index
    int get(int index) {
        if (index < 0 || index >= length) {
            cout << "Error: Index out of bounds!" << endl;
            return -1;  // Return sentinel value
        }
        return arr[index];
    }

    // Update element at specific index
    void update(int index, int value) {
        if (index < 0 || index >= length) {
            cout << "Error: Index out of bounds!" << endl;
            return;
        }
        arr[index] = value;
    }

    // Get the array pointer (for external access)
    int* getArrayPointer() {
        return arr;
    }

    // Get current capacity
    int getCapacity() {
        return capacity;
    }

    // Get current length
    int getLength() {
        return length;
    }

    // Search for a value and return its index
    int search(int value) {
        for (int i = 0; i < length; i++) {
            if (arr[i] == value) {
                return i;
            }
        }
        return -1;  // Not found
    }

    // Clear all elements
    void clear() {
        length = 0;
        curr = arr;  // Reset curr pointer
    }

    // Print all elements
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

    // Get current pointer position
    int getCurrPosition() {
        return (curr - arr);
    }

    // Move current pointer to start
    void start() {
        curr = arr;
    }

    // Move current pointer to end
    void end() {
        curr = arr + (length - 1);
    }

    // Move current pointer to next position
    void next() {
        if (curr < arr + (length - 1)) {
            curr++;
        }
    }

    // Move current pointer to previous position
    void back() {
        if (curr > arr) {
            curr--;
        }
    }

    // Get value at current pointer
    int getValue() {
        if (isEmpty()) {
            cout << "Error: Array is empty!" << endl;
            return -1;
        }
        return *curr;
    }

    // Set value at current pointer
    void setValue(int value) {
        if (curr >= arr && curr < arr + length) {
            *curr = value;
        }
    }
};

int main() {
    // Test the ArrayList
    ArrayList list(5);  // Start with capacity 5
    
    cout << "=== Testing ArrayList ===" << endl;
    
    // Insert elements
    cout << "\n1. Inserting elements:" << endl;
    for (int i = 1; i <= 10; i++) {
        list.insert(i * 10);
        cout << "Inserted " << i * 10 << ", Length: " << list.getLength() 
             << ", Capacity: " << list.getCapacity() << endl;
    }
    
    // Print all elements
    cout << "\n2. Current array:" << endl;
    list.print();
    
    // Insert at specific positions
    cout << "\n3. Inserting at specific positions:" << endl;
    list.insertAt(2, 99);
    list.insertAtStart(5);
    list.insertAt(list.getLength(), 100);
    list.print();
    
    // Get array pointer and access externally
    cout << "\n4. Accessing array via pointer:" << endl;
    int* arrPtr = list.getArrayPointer();
    cout << "First element via pointer: " << arrPtr[0] << endl;
    cout << "Third element via pointer: " << arrPtr[2] << endl;
    
    // Test removal
    cout << "\n5. Testing removal:" << endl;
    list.removeAt(2);
    cout << "After removing at index 2: ";
    list.print();
    
    list.remove();
    cout << "After removing last: ";
    list.print();
    
    list.removeFromStart();
    cout << "After removing first: ";
    list.print();
    
    // Test search
    cout << "\n6. Testing search:" << endl;
    int searchVal = 50;
    int index = list.search(searchVal);
    if (index != -1) {
        cout << "Found " << searchVal << " at index " << index << endl;
    } else {
        cout << searchVal << " not found in array" << endl;
    }
    
    // Test update
    cout << "\n7. Testing update:" << endl;
    list.update(0, 999);
    cout << "After updating index 0 to 999: ";
    list.print();
    
    // Test current pointer operations
    cout << "\n8. Testing current pointer operations:" << endl;
    list.start();
    cout << "Start value: " << list.getValue() << endl;
    
    list.next();
    cout << "After next(): " << list.getValue() << endl;
    
    list.setValue(888);
    cout << "After setValue(888): ";
    list.print();
    
    // Test clear
    cout << "\n9. Testing clear:" << endl;
    list.clear();
    cout << "After clear - ";
    list.print();
    
    return 0;
}