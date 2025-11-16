#include<iostream>
using namespace std;
// returnType  functionName (Arguments/Parameters) {}
void mysecretFunc(int S){
	cout << S;
}
int main()
{
// returnType (*functionPointer)(Arguments/ParametersType) = &fucntionName ; 	
	void (*func)(int) = &mysecretFunc;
// (*functionPointer)(Arguments) ;
	(*func)(55);
	return 0;
}