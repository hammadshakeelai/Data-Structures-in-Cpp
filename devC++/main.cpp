#include<iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main(){
	auto start = high_resolution_clock::now();   // start time
	//---------------------------------------------------------------
	int NumberOfP;
	
	cout<<"What is number of participants: ";
	cin>>NumberOfP;
	int *ptrArray= new int[NumberOfP];
	for(int i=0;i<NumberOfP;i++){
		ptrArray[i]=0;
	}
	for(int i=0;i<NumberOfP;i++){
		cout<<"Is Participant Number [ "<<i+1<<" ] Present (0/1): ";
		cin>>ptrArray[i];
	}
	cout<<"\n\n|Now Displaying Attendence|\n";
	for(int i=0;i<NumberOfP;i++){
		cout<<"Participant Number  [ "<<i+1<<" ] is "<<(ptrArray[i]?"Present.\n":"Absent.\n");
	}
	delete [] ptrArray;
    //---------------------------------------------------------------
    auto end = high_resolution_clock::now();     // end time
    auto duration = duration_cast<milliseconds>(end - start);

    cout << "\nExecution time: " << duration.count() << " ms\n";
    return 0;
}