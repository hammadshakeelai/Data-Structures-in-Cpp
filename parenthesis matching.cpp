#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isBalanced(string expr) {
    stack<char> s;

    for (char c : expr) {
        // If opening bracket, push the EXPECTED closing bracket
        if (c == '(') s.push(')');
        else if (c == '{') s.push('}');
        else if (c == '[') s.push(']');
        
        // If closing bracket (and not just random text)
        else if (c == ')' || c == '}' || c == ']') {
            // If stack is empty OR top doesn't match current char
            if (s.empty() || s.top() != c) return false;
            s.pop();
        }
    }
    // If stack is empty, everything matched perfectly
    return s.empty();
}

int main() {
    string e = "{([])}";
    if (isBalanced(e)) cout << "Balanced";
    else cout << "Not Balanced";
    return 0;
}