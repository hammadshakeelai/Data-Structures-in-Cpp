#include <iostream>
using namespace std;

int main() {
	int reversed_num = 0, remainder;
	int num,temp;
	cout << "enter a number: ";
	cin >> num;
	temp = num;
	while (num != 0) {
		remainder = num % 10;
		reversed_num = reversed_num * 10 + remainder;
		num /= 10;
	}
	cout << "Reversed Number: " << reversed_num << endl;
	num = temp;
	cout << "Number: " << num << endl;
	(num == reversed_num) ? cout << "palindrome" : cout << "not palindrome";
    return 0;
}