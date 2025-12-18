#include <iostream>
using namespace std;
int main()
{
    int arr[] = { 5,4,3,2,1 };
    int n = 5;
    int temp;
    for (int i = 0; i < n - 1; i++) {
        temp = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[temp] <= arr[j]) {
                continue;
            }
            else {
                temp = j;
            }
        }
        if (i==temp)
            continue;
        arr[temp] = arr[temp] ^ arr[i];
        arr[i] = arr[temp] ^ arr[i];
        arr[temp] = arr[temp] ^ arr[i];
    }
	for (int i = 0; i < 5; i++)
	    cout << arr[i] << " ";
    return 0;
}