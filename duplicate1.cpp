#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30, 20, 40}; // '20' is the duplicate
    int n = 5; // Size of array

    for (int i = 0; i < n; i++) {
        // Check the rest of the array (j = i + 1)
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                cout << "Found Duplicate: " << arr[i] << endl;
            }
        }
    }
    return 0;
}