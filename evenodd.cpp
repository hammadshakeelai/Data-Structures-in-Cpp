#include <iostream>
using namespace std;

int main(){
	int arr[]={1,2,3,5,6,8};
	int n=6;
	for(int i =0;i<6;i++){
	
	cout<<arr[i]<<"";}
	cout<<endl;
	int* evenptr = arr;
	int* oddptr = arr+1;
	
	while(evenptr < arr+n && oddptr < arr+n){
		if(*evenptr %2 == 0 && *oddptr %2 !=0){
		
		 evenptr +=2;
		 oddptr +=2;
	}
		 
		 else if(*evenptr %2 !=0 && *oddptr %2 ==0){
		 
		 int temp= *evenptr;
		 *evenptr = *oddptr;
		 *oddptr = temp;
	}
	
	else if(*evenptr %2 == 0){
		evenptr +=2;
	}
	
	else if(*oddptr %2 != 0){
		oddptr +=2;
		
	}
	
	}
	
	for(int i=0;i<6;i++){
		cout<<arr[i]<<"";}
		cout<<endl;
		
		return 0;
	}
	
