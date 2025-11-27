#include<iostream>
using namespace std;
#define MAX 100
class Stack {
    int top;
    int arr[MAX];
public: 
    Stack() { top = -1; }
    bool isFull() {
        return top == MAX - 1;
    }
    bool isEmpty() {
        return top == -1;
    }
    void push(int x) {
        if (isFull()) {
            cout << "Stack Overflow\n";
            return;
        }
        arr[++top] = x;
    }
    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow\n";
            return -1;
        }
        return arr[top--];
    }
    int peek() {
        if (isEmpty()) {
            cout << "Stack is Empty\n";
            return -1;
        }
        return arr[top];
    }
    void display() {
        if (isEmpty()) {
            cout << "Stack is Empty\n";
            return;
        }
        for (int i = top; i >= 0; i--) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    
};
bool areBracketsBalanced(string expression) {
    Stack stack;
    for (char ch : expression) {
        if (ch == '(' || ch == '{' || ch == '[') {
            stack.push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (stack.isEmpty()) return false;
            char top = stack.pop();
            if ((ch == ')' && top != '(') ||
                (ch == '}' && top != '{') ||
                (ch == ']' && top != '[')) {
                return false;
            }
        }
    }
    return stack.isEmpty();
}
int main() {
    cout << areBracketsBalanced("{[()]}") << endl; // Output: 1 (true)
    cout << areBracketsBalanced("{[()[]]}") << endl; // Output: 1 (true)
    return 0;
}