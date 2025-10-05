#include <iostream>
using namespace std;
void print(int c,char d){
    cout<<c<<" "<<d<<endl;
}
// Function pointer type
// return_type (*pointer_name)(parameter_types);
int main() {
    // Declare a function pointer
    void (*funcPtr)(int, char);
    // Assign the address of the function to the pointer
    funcPtr = &print;
    // Call the function using the pointer
    funcPtr(42, 'A');
    return 0;
}