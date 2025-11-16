#include<iostream>
#include<cstdlib>
using namespace std;
int main()
{
	//int*p=  (returnType*) malloc (size_of_space_to_be_allocated)
	int *ptr = (int*)malloc(sizeof(int));//array of bytes
	*ptr = 1;
	cout << *ptr;//test
	free(ptr);
	return 0;
}// O(n)