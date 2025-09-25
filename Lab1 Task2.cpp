#include<iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;


int generateCode(int n){
	if(n==0){
		return 1;
	}
	else if(n<0){
		cout<<"\nError \n--The Number Should be Less Then ";
		return 0;
	}
	
	int factorial = 1;
	for(int i=n;i>1;i--){
		factorial*=i;
	}
	return factorial;
}

int main(){
	auto start = high_resolution_clock::now();   // start time
	//---------------------------------------------------------------
	int (*codePtr)(int)=&generateCode;
	int code;
	cout<<"Enter A Number: ";
	cin>>code;
	if(code!=0){
		cout<<"Your Secret Code is: ";
	}
	cout<<(*codePtr)(code);
    //---------------------------------------------------------------
    auto end = high_resolution_clock::now();     // end time
    auto duration = duration_cast<milliseconds>(end - start);

    cout << "\nExecution time: " << duration.count() << " ms\n";
    return 0;
}