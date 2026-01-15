#include <iostream>
#include <stack>
#include <string>
#include <cctype> // for isdigit

using namespace std;

int main() {
    stack<int> s;
    string exp = "53+82-*"; // Equivalent to: (5 + 3) * (8 - 2)

    for (char c : exp) {
        if (isdigit(c)) {
            s.push(c - '0'); // Convert char to int
        } else {
            int val2 = s.top(); s.pop();
            int val1 = s.top(); s.pop();

            if (c == '+') s.push(val1 + val2);
            else if (c == '-') s.push(val1 - val2);
            else if (c == '*') s.push(val1 * val2);
            else if (c == '/') s.push(val1 / val2);
        }
    }

    cout << "Result: " << s.top() << endl; // Output should be 48
    return 0;
}