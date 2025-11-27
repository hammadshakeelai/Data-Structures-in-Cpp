#include<iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;
#define size 10
// --- <stack>
class Stack{
	public:
		int* arr;
		int top;
		int maxSize;
		Stack(){
			arr = new int[size];
			top = -1;
			maxSize = size;
		}
		void Stack_New(int s){
			top = -1;
			arr = new int[s];
			maxSize = size;
		}
		void push(int value){(top != maxSize)?(arr[++top] = value):(cout<<"Stack Overflow"<<endl);}
		int pop(){(top == -1)?(cout<<"Stack Underflow"<<endl;return -1):return arr[top--];}
		int peek(){(top == -1)?cout<<("Stack Underflow"<<endl;return -1):return arr[top];}
		void display(){
			if(top==-1){
				cout<<"Stack Underflow"<<endl;
				return
			}
			for(int i=0;i<=top;i++){
				cout<<arr[i]<<" ";
			}
			cout<<endl;
		}
};
bool areBracketsBalanced(string expr){
	Stack st;
	for(char ch : expr){
		if ( ch == '{' || ch =='[' || ch == '<' || ch == '('){
			st.push(ch);
		}
		else if ( ch == '}' || ch ==']' || ch == '>' || ch == ')'){
			if (ch == st.peek();)
				st.pop(ch);
			else
				return false;
		}
	}
	if(st.top != -1)
		return false;
	return true;
}
int main() {
	auto start = high_resolution_clock::now();   // start time
	//---------------------------------------------------------------
	cout<<areBracketsBalanced("{{}}")
	//---------------------------------------------------------------
	auto end = high_resolution_clock::now();     // end time
	auto duration = duration_cast<milliseconds>(end - start);

	cout << "\nExecution time: " << duration.count() << " ms\n";
	return 0;
}