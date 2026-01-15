#include <iostream>
#include <stack>
using namespace std;

int main() {
    // 0=HALT, 1=PRINT, 2=CALL target, 3=RET
    // Code: Print -> Call index 6 -> Print -> Halt ... [Func: Print -> Ret]
    int ram[] = { 1, 2, 6, 1, 0, 0, 1, 3 }; 
    
    int ip = 0;              // Instruction Pointer
    stack<int> returnStack;  // The Stack

    while (ram[ip] != 0) {   // Loop until HALT
        int opcode = ram[ip];

        if (opcode == 1) {          // PRINT (Do work)
            cout << "Exec: " << ip << endl;
            ip++;                   // Move to next line
        }
        else if (opcode == 2) {     // CALL (Jump)
            int target = ram[ip+1]; // Read where to go
            returnStack.push(ip+2); // Save return address (Skip opcode + arg)
            ip = target;            // Force Jump
        }
        else if (opcode == 3) {     // RET (Return)
            ip = returnStack.top(); // Restore old address
            returnStack.pop();
        }
    }
    return 0;
}