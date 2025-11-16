#include<iostream>
#include<cstdlib>
using namespace std;
int main()
{
	//int*p=  (returnType*) calloc (size_of_type_to_be_allocated)
	int *ptr = (int*)calloc(1,sizeof(int));//behave like array of pointer to the arrays of bytes
	*ptr = 1;
	cout << *ptr;
	free(ptr);
	return 0;
}